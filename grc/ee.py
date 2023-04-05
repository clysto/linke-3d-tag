import pyglet

window = pyglet.window.Window()
batch = pyglet.graphics.Batch()

teapot = pyglet.model.load('teapot.obj', batch=batch)

@window.event
def on_draw():
    batch.draw()

pyglet.app.run()