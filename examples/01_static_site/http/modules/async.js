
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
