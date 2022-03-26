
import * as A from "/modules/async.js";
import * as UI from "/modules/dom.js";


export function start() {    
      
  // event handler       
  UI.getId("sideBarToggle").addEventListener("click", sideBarToggle);
  
  A.get("/user/list", ()=>{
    
  });
  
}

function hashChange() {
  let loc = location.hash;
  console.debug(loc);
  let panel = UI.getId("contents");
  
  if(loc === "#intro") {
      A.getPage("introduction.html", panel);
  } else if(loc === "#setup") {
      A.getPage("setup.html", panel);
  }
  
  sideBarToggle(); 
}

function sideBarToggle() {
  let sideBar = UI.getId("sidebar");  
     
  if(sideBar.classList.contains("w3-hide")) {
    sideBar.classList.remove("w3-hide");                
  } else {
    sideBar.classList.add("w3-hide");       
  }
}

