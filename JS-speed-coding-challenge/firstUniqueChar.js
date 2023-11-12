box.firstUniqueChar = function firstUniqueChar(x) {
  // x is a string
  // return a string
  // (ex. x="toptal", you should return "o" because "t" appeared twice)
  let result = {};
  for (let i = 0; i < x.length; i++)
    !result[x[i]] ? result[x[i]]=1 : result[x[i]]++;
  for (let key of Object.keys(result))
  {
    if (result[key] == 1)
      return x[x.indexOf(key)];
  }
  return (false);
};
