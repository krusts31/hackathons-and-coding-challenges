box.romanToInt = function romanToInt(x) {
  const conversoin = {"M": 1000, "D":500, "C":100, "L":50, "X":10, "V":5, "I":1}

  const arr = x.split('');
  
  let total = 0;
  let current;
  let currentValue;
  let next;
  let nextValue;

  for (let i = 0; i < arr.length; i++)
  {
  current = arr[i]
    currentValue = conversoin[current]
    next = arr[i+1]
    nextValue = conversoin[next]
    if (currentValue < nextValue)
      total -= currentValue;
    else
      total += currentValue;
  }
  return total
};

console.log(romanToInt("XII"))
