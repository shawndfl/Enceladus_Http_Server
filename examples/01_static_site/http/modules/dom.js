
/**
 * select something from the root
 */
export function sel(id) {
  let dom = document.querySelectorAll(id);
  if(dom == undefined) {
    console.error("cannot find " + id);
  }
  return dom;
}

/**
 * gets an id from the document
 */
export function getId(documentId) {
  let value = document.getElementById(documentId);
  if(value == undefined) {
    console.error(documentId + " not found");
  }
  return value;
}