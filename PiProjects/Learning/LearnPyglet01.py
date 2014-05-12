import pyglet

window = pyglet.window.Window(resizable=True)

@window.event
def on_draw():
    window.clear()
    pyglet.gl.glColor4f(1.0,0,0,1.0)
    pyglet.graphics.draw(2, pyglet.gl.GL_LINES,
        ('v2i', (10, 15, 30, 35))
    )

pyglet.app.run()
