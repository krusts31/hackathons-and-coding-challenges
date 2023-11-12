box.numberOfCircles = function numberOfCircles(x) {
  // x is a number
  // return a number
  // (ex. x=1908, you should return 4)
  // (ex. x=9 you should return 1)
  let cnt = 0;
  x = x.toString();
  for (let i = 0; i < x.length; i++) {
    if (x[i] == '6')
      cnt++;
    if (x[i] == '9')
      cnt++;
    if (x[i] == '0')
      cnt++;
    if (x[i] == '8')
      cnt = cnt + 2;
  }
  return (cnt);
}
