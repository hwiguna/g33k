var email   = require("../node_modules/emailjs/email");
var server  = email.server.connect({
   user:    "hari.wiguna.demo", 
   password:"panggung", 
   host:    "smtp.gmail.com", 
   ssl:     true
});

// send the message and get a callback with an error or details of the message that was sent
server.send({
   text:    "My bowl is empty! Please feed me.", 
   from:    "The Cat <meow@scratch.com>", 
   to:      "hwiguna <hwiguna@gmail.com>",
   cc:      "",
   subject: "Hungry"
}, function(err, message) { console.log(err || message); });