/*jshint strict:true node:true es5:true onevar:true laxcomma:true laxbreak:true*/
/*
 * SERVER
 */
(function () {
  "use strict";

  var steve = require('./steve')
    , connect = require('http')
    , app = connect.createServer(websocket)
    , Socket = require('socket.io')
    , io = Socket.listen(80, { "destroy upgrade": false })
    ;

  io.sockets.on('connection', function (socket) {
    console.log('Duino socket open');
    socket.emit('browserConnected');
    console.log('user number '+socket.id+' signed in');
    socket.on('message', function (data) {
      console.log(data);
    });
    socket.on('disconnect', function () { 
      console.log('deleted user '+socket.id);
    });
    socket.on('close', function () { 
      console.log('ClOsEd Socket');
    });
    socket.on('error', function (err) { 
      console.log(err);
    });
  });


  function getHello(request, response) {
    response.json(request.params);
    response.end();
  }

  function websocket(request, response) {
    console.log('Duino made a GET request');
    response.end();
  }

  /*function router(rest) {
    rest.get('/hello/:name?', getHello);
    rest.get('/websocket', websocket);
  }

  app
    .use(steve)
    .use(connect.router(router))
    ;*/

  module.exports = app;
}());
