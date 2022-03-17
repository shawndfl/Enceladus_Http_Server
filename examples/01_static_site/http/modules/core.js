
import * as Async from "/modules/async.js";
import * as UI from "/modules/dom.js";

export function start() {
  var panel = UI.sel("#panel1");
  
  Async.get("/panel.html", (text)=>{    
    if(panel.length > 0) { 
      panel[0].innerHTML = text;
    }           
  });     
}
