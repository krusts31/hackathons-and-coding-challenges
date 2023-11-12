box.numberRepresentation = function numberRepresentation(arr) {
  alpha="abcdefghijklmnopqrstuvwxyz"
  let alpha_i = 0;
  arr = arr.sort();
  let ret = [];
  let i = 0;
  let fin = 0;
  let arr_i = 0
  while (i < arr.length)
  {

    if (alpha[alpha_i] == arr[i])
    {
      ret.push(0)
      while (alpha[alpha_i] == arr[i])
      {
        ret[arr_i]++;
        i++;
        if (i > arr.length)
        {
          for (let x = 0; x < ret.length; x++)
            fin = fin * 10 + ret[x]
          return (fin)
        }
      }
      arr_i++;
    }
    else
      alpha_i++;
  }
  for (let x = 0; x < ret.length; x++)
    fin = fin * 10 + ret[x]
  return (fin)
}
