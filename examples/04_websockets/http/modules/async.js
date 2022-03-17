
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
    
    this.ws.onopen = ()=> {
      console.debug("Open connection")      
    };

    this.ws.onmessage = (evt) => {
      let data = evt.data;
      console.debug(data)
      if(onMessage != undefined) {        
        onMessage();
      }
    };

    this.ws.onclose = () => {

      // websocket is closed.
      console.debug("closing");
    };

  }  
    
  send(data) {    
    this.ws.send(data);  
  }
  
}