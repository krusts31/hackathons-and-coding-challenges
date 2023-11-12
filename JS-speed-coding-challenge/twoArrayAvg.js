box.twoArrayAvg = function twoArrayAvg(x, y) {
  // x and y are arrays of numbers
  // return a number
  // (ex. x=[1,2,3],  y=[4,5,6], you should return 3.5)
  var total = 0;
  for(var i = 0; i < x.length; i++) {
    total += x[i];
  }
  let one = ((total / x.length));
  var total = 0;
  for(var i = 0; i < y.length; i++) {
    total += y[i];
  }
  let two = ((total / y.length));
  return ((one + two) / 2)
};
