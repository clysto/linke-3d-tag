import pyglet
from pyglet.graphics.shader import Shader, ShaderProgram
from pyglet.gl import glEnable, GL_DEPTH_TEST, GL_CULL_FACE

batch = pyglet.graphics.Batch()

glEnable(GL_DEPTH_TEST)
glEnable(GL_CULL_FACE)

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

vert_shader = Shader(vertex_source, 'vertex')
frag_shader = Shader(fragment_source, 'fragment')
program = ShaderProgram(vert_shader, frag_shader)
pyglet.graphics.get_default_shader()

position_data = (1, 1, 1, 2, 2, 2)

vlist = program.vertex_list(
    3,
    pyglet.gl.GL_TRIANGLES,
    batch=batch,
    position=("i", position_data),
    colors=("Bn", [255, 0, 0] * 3),
)
print(list(vlist.position))

window = pyglet.window.Window()


@window.event
def on_draw():
    window.clear()
    batch.draw()


pyglet.app.run()
