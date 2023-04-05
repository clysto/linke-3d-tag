import concurrent.futures
import math
from struct import unpack
from pyglet.graphics.shader import Shader, ShaderProgram

import numpy as np
import pyglet
from pyglet import gl, window
from scipy.spatial.transform import Rotation as R

x_angle = 0
y_angle = 0
z_angle = 0


def load_texture(file_name):
    texture = pyglet.image.load(file_name).get_texture()
    gl.glTexParameterf(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_NEAREST)
    gl.glTexParameterf(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_NEAREST)
    return pyglet.graphics.TextureGroup(texture)


def make_textures(textures):
    result = {}
    base = "assets/textures"
    faces = ("left", "right", "top", "bottom", "front", "back")
    for face in faces:
        file_name = textures.get(face, textures.get("side"))
        result[face] = load_texture(f"{base}/{file_name}")
    return result


def get_vertices(x, y, z, rotation):
    dx = 0.5
    dy = 0.005
    dz = 0.2

    a = (-dx, -dy, dz)
    b = (dx, -dy, dz)
    c = (dx, dy, dz)
    d = (-dx, dy, dz)
    e = (-dx, -dy, -dz)
    f = (dx, -dy, -dz)
    g = (dx, dy, -dz)
    h = (-dx, dy, -dz)

    r = R.from_euler("xyz", rotation)
    a, b, c, d, e, f, g, h = r.apply([a, b, c, d, e, f, g, h])

    return [
        np.hstack((a, e, h, d)),  # side
        np.hstack((b, f, g, c)),  # side
        np.hstack((d, c, g, h)),  # top
        np.hstack((b, a, e, f)),  # bottom
        np.hstack((a, b, c, d)),  # side
        np.hstack((e, f, g, h)),  # side
    ]


class TagModel:
    textures = make_textures(
        {
            "side": "tag51-side.png",
            "top": "tag51-top.png",
            "bottom": "tag51-bottom.png",
        }
    )


vertex_source = """#version 150 core
    in vec2 position;
    in vec4 colors;
    out vec4 vertex_colors;

    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * vec4(position, 0.0, 1.0);
        vertex_colors = colors;
    }
"""
fragment_source = """#version 150 core
    in vec4 vertex_colors;
    out vec4 final_color;

    void main()
    {
        final_color = vertex_colors;
    }
"""


class Model:
    def __init__(self):
        self.batch = pyglet.graphics.Batch()
        self.program = pyglet.shapes.get_default_shader()
        self.vlist = self.program.vertex_list(
            6,
            gl.gl.GL_TRIANGLES,
            self.batch,
        )

    def update(self):
        self.batch = pyglet.graphics.Batch()
        # self.draw_block((0, 0, 0), TagModel)

    def draw_block(self, position, block):
        global x_angle, y_angle, z_angle
        vertices = get_vertices(*position, [x_angle, y_angle, z_angle])
        faces = ("left", "right", "top", "bottom", "front", "back")
        for vertex, face in zip(vertices, faces):
            self.program.vertex_list(
                4,
                gl.GL_QUADS,
                self.batch,
            )
            # self.batch.add(
            #     4,
            #     gl.GL_QUADS,
            #     block.textures[face],
            #     ("v3f/static", vertex),
            #     (
            #         "t2f/static",
            #         (
            #             0,
            #             0,
            #             0.796875,
            #             0,
            #             0.796875,
            #             0.65234375,
            #             0,
            #             0.65234375,
            #         ),
            #     ),
            # )


class Player:
    def __init__(self, position=(0, 0, 1), rotation=(0, 0)):
        self.position = position
        self.rotation = rotation
        self.strafe = [0, 0, 0]  # forward, up, left

    def mouse_motion(self, dx, dy):
        x, y = self.rotation
        sensitivity = 0.15
        x += dx * sensitivity
        y += dy * sensitivity
        y = max(-90, min(90, y))
        self.rotation = x % 360, y

    def update(self, dt):
        motion_vector = self.get_motion_vector()
        speed = dt * 5
        self.position = [x + y * speed for x, y in zip(self.position, motion_vector)]

    def get_motion_vector(self):
        x, y, z = self.strafe
        if x or z:
            strafe = math.degrees(math.atan2(x, z))
            yaw = self.rotation[0]
            x_angle = math.radians(yaw + strafe)
            x = math.cos(x_angle)
            z = math.sin(x_angle)
        return x, y, z


def draw_camera(position, rotation):
    yaw, pitch = rotation
    gl.glRotatef(yaw, 0, 1, 0)
    gl.glRotatef(-pitch, math.cos(math.radians(yaw)), 0, math.sin(math.radians(yaw)))
    x, y, z = position
    gl.glTranslatef(-x, -y, -z)


def set_3d(width, height):
    gl.glEnable(gl.GL_DEPTH_TEST)
    gl.glMatrixMode(gl.GL_PROJECTION)
    gl.glLoadIdentity()
    gl.gluPerspective(65, width / height, 0.1, 60)
    gl.glMatrixMode(gl.GL_MODELVIEW)
    gl.glLoadIdentity()


class Window(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # self.player = Player()
        self.model = Model()
        # self.set_exclusive_mouse(True)
        # self.is_pause = False
        # pyglet.clock.schedule(self.update)

    # def pause(self):
    #     self.is_pause = True
    #     self.set_exclusive_mouse(False)

    # def on_mouse_motion(self, x, y, dx, dy):
    #     if not self.is_pause:
    #         self.player.mouse_motion(dx, dy)

    # def on_mouse_press(self, x, y, button, modifiers):
    #     self.is_pause = False
    #     self.set_exclusive_mouse(True)

    # def on_key_press(self, symbol, modifiers):
    #     if symbol == window.key.ESCAPE:
    #         self.pause()
    #     elif symbol == window.key.Q:
    #         self.close()
    #     speed = 1
    #     if symbol == window.key.W:
    #         self.player.strafe[0] = -speed
    #     elif symbol == window.key.S:
    #         self.player.strafe[0] = speed
    #     elif symbol == window.key.A:
    #         self.player.strafe[2] = -speed
    #     elif symbol == window.key.D:
    #         self.player.strafe[2] = speed
    #     elif symbol == window.key.SPACE:
    #         self.player.strafe[1] = speed
    #     elif symbol == window.key.LSHIFT:
    #         self.player.strafe[1] = -speed

    # def on_key_release(self, symbol, modifiers):
    #     if symbol == window.key.W:
    #         self.player.strafe[0] = 0
    #     elif symbol == window.key.S:
    #         self.player.strafe[0] = 0
    #     elif symbol == window.key.A:
    #         self.player.strafe[2] = 0
    #     elif symbol == window.key.D:
    #         self.player.strafe[2] = 0
    #     elif symbol == window.key.SPACE:
    #         self.player.strafe[1] = 0
    #     elif symbol == window.key.LSHIFT:
    #         self.player.strafe[1] = 0

    # def update(self, dt):
    #     self.player.update(dt)
    #     self.model.update()

    def on_draw(self):
        self.clear()
        # set_3d(*self.get_size())
        # draw_camera(self.player.position, self.player.rotation)
        self.model.batch.draw()


def gr_receiver():
    pass
    # global x_angle, z_angle, y_angle
    # sock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    # sock.sendto(b"0", ("127.0.0.1", 52001))
    # # def on_sigint():
    # #     sock.shutdown(socket.SHUT_WR)
    # # signal.signal(signal.SIGCLD, on_sigint)
    # while True:
    #     data = sock.recvfrom(34)[0]
    #     x, y, z = unpack("hhh", data[:6])
    #     x_angle = math.atan(x / math.sqrt(y**2 + z**2))
    #     z_angle = math.atan(y / math.sqrt(x**2 + z**2))
    #     y_angle = math.atan(math.sqrt(x**2 + y**2) / z)
    # print(x_angle, y_angle, z_angle)


def main():
    Window(width=800, height=480, resizable=True)
    # gl.glClearColor(0, 0, 0, 1)  # black
    pyglet.app.run()


if __name__ == "__main__":
    main()
