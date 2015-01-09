Pyglet Event Framework
======================
pyglet.window, app, text, and media use a consistent event pattern
The event pattern provides multiple ways to attach Event Handlers to objects

Event Dispatcher
================
Object that has events it needs to notify other objects about
pyglet-provided event dispatchers: Window, Player
User-defined Event Dispatchers are possible as well, but complicated
An Event Dispatcher must :
    1. Be a subclass of EventDispatcher
    2. Call register_event_type class method on subclass
         for each event the subclass will recognize
    3. Call dispatch_event to create and dispatch event
         as needed

Event Handler
=============
Function with formal parameter list corresponding to event type
that can be attached to an Event Dispatcher

e.g. Window.on_resize is an event with parameters (width, height)
so an Event Handler for this event could be the function:

  def on_resize(width, height):
      pass

  Attaching an Event Handler
------------------------------
  Attaching event, Window.on_resize to Event Dispatcher, ( ), via Event Handler

    window = pyglet.window.Winder()

    def on_resize(width, height):
        pass
    window.on_resize = on_resize

      -OR-

    window = pyglet.window.Winder()

    @window.event
    def on_resize(width, height):
        pass

  This will not replace the event handler on the object, but rather add
  the event handler onto the event handler stack of the object.

  Stacking Event Handlers
---------------------------

    It is convenient to attach more than one Event Handlers
    to an object.  EventDispatchers allows you to stack event handlers
    on top of each other, rather than replacing them.
    The even will propagate from the top of the Event Handler stack to
    the bottom.
    To push an event handler onto the stack of an object,
     you can use push_handlers:

      def on_key_press(symbol, modifiers):
          if symbol == key.SPACE:
              fire_laser()
      window.push_handlers(on_key_press)

        -OR-

      @window.event
      def on_key_press(symbol, modifiers):
          if symbol == key.SPACE:
              fire_laser()

    This allows for the event handler to execute, and then move on to the next
    event handler in the stack (e.g. Window has_exit() event handler for ESC key)

    If you do not want the remaining event handlers to be accessed,
    you can return True for any event handler

      def on_key_press(symbol, modifiers):
          if symbol == key.SPACE:
              fire_laser()
              return True
      window.push_handlers(on_key_press)


    You can push multiple handlers at once (with multiple arguments passed to
    push_handlers() ), and remove handlers with pop_handlers() which removes
    any Event Handler passed to it, or the top level of Event Handler(s), if
    no arguments are given. If multiple Event Handlers are passed at once,
    they will be removed together during a pop_handlers() call

      class GameEventHandler(object):
          def on_key_press(self, symbol, modifiers):
              return True

          def on_mouse_press(self, x, y, button, modifiers):
              return True

      game_handlers = GameEventHandlers()

      def start_game()
          window.push_handlers(game_handlers)

      def stop_game()
          window.pop_handlers()

