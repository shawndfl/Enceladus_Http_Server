
import * as A from "/modules/async.js";
import * as UI from "/modules/dom.js";


export function start() {    
      
  // event handler       
  UI.getId("sideBarToggle").addEventListener("click", sideBarToggle);
  
  // initialize the correct page
  hashChange();
  
  window.addEventListener("hashchange", hashChange);  
}

function hashChange() {
  let loc = location.hash;
  console.debug(loc);
  let panel = UI.getId("contents");
  
  if(loc === "#setup" || loc =="") {
      A.getPage("setup.html", panel);
  } else if(loc === "#api") {
      A.getPage("setup.html", panel);
  }   
}

function sideBarToggle() {
  let sideBar = UI.getId("sidebar"); 
  let main = UI.getId("main");
  let titleBar = UI.getId("titleBar");
  
  if(sideBar.style.display=="block") {
      sideBar.style.display="none";   
      main.style.marginLeft ="0px";   
      titleBar.style.marginLeft ="0px";
  } else {    
      sideBar.style.display="block";
      main.style.marginLeft ="200px";
      titleBar.style.marginLeft ="200px";
          
  }
}

