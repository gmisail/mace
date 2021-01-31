const PORT = 55454;
const IP = "127.0.0.1";

const dgram = require("dgram");
const server = dgram.createSocket("udp4");

console.log("[mace] Starting server...");

server.on('listening', () => {
    let address = server.address();

    console.log("[mace] Listening on " + address.address + ":" + address.port);
});

server.on('message', (message, remote) => {
    console.log("[mace] " + message);
});

server.bind(PORT, IP);

