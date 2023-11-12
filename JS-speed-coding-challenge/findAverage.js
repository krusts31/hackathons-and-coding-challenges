box.findAverage = function findAverage(x) {
  // x is an array of numbers
  // return a number
  // (ex. x=[1,2,3,4] then you should return 3 because the average is 2.5)
var total = 0;
for(var i = 0; i < x.length; i++) {
    total += x[i];
}
return (Math.ceil(total / x.length));
};
