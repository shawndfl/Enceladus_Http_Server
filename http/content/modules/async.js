
/**
 * runs a remote get request
 */
export function get(path, onload) {

  fetch(path)
    .then(response => response.text())
    .then(result => {
      if (onload != undefined) {
        onload(result);
      }
    });
}


export class Socket {
  connect(url, onMessage) {
    this.ws = new WebSocket(url);
    
    this.ws.onopen = function() {
      // Web Socket is connected, send data using send()
      ws.send("Testing");
      alert("Message is sent...");
    };

    this.ws.onmessage = function(evt) {
      let data = evt.data;
      console.debug(data)
      if(onMessage != undefined) {        
        onMessage();
      }
    };

    this.ws.onclose = function() {

      // websocket is closed.
      console.debug("closing");
    };

  }  
    
  send(data) {    
    this.ws.send(data);  
  }
  
}