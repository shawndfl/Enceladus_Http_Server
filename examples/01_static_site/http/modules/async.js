
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
    })
    .catch((error) => { console.log(error); });
}

/**
 * runs a remote get request
 */
export function getJson(path, onload) {

  fetch(path)
    .then(response => response.text())
    .then(result => {
      if (onload != undefined) {
        onload(JSON.parse(result));
      }
    })
    .catch((error) => { console.log(error); });    
}

export function post(path, data, onload) {

  fetch(path, {
    method: "POST",
    body: JSON.stringify(data)
  })
    .then(response => response.text())
    .then(result => {
      if (onload != undefined) {
        onload(result);
      }
    })
    .catch((error) => { console.log(error); });
}

/**
 * Loads a page and assigns it to the domParent innerHTML
 */
export function getPage(path, domParent, onload) {

  fetch(path, {
    method: "GET"    
  })
    .then(response => response.text())
    .then(result => {
      domParent.innerHTML = result;
      if (onload != undefined) {
        onload(result);
      }
    })
    .catch((error) => { console.log(error); });
}
