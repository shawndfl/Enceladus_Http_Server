
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