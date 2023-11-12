box.matchingType = function matchingType(x, y) {
  // x and y are random types 
  // return boolean
  // (ex. x = 7 and y = "Toptal", should return false),
  // (ex. x = 10 and y = 100, should return true),
  var toType = function(obj) {
  return ({}).toString.call(obj).match(/\s([a-zA-Z]+)/)[1].toLowerCase()
}
return (toType(x) === toType(y));
};
