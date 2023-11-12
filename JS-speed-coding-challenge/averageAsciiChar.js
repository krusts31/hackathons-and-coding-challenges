box.averageAsciiChar = function averageAsciiChar(x) {

  let arr = [];
  len = x.toString().length;
  for (let i =0; len > i; i++)
  {
    arr.push(x[i].charCodeAt(0))
  }
  var total = 0;
  for(var i = 0; i < x.length; i++) {
    total += arr[i];
  }
  let one = (total / arr.length);

  return (String.fromCharCode(Math.round(one)))
};
