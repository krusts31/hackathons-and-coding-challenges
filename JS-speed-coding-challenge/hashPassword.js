box.hashPassword =function hashPassword(password, x) {
  // password is a string, x is a number
  // return a string
  // (ex. password = 'ab1By', x = 3 so you should return "DE4eB")
  var swapCase = function(letters){
    var newLetters = "";
    for(var i = 0; i<letters.length; i++){
        if(letters[i] === letters[i].toLowerCase()){
            newLetters += letters[i].toUpperCase();
        }else {
            newLetters += letters[i].toLowerCase();
        }
    }
    return newLetters;
  }
  let arr = [];
  let hit = 0;
  for (let i =0; password.length > i; i++)
  {
    let val = password[i].charCodeAt(0)
    if (val >= 65 && val <= 90 || 97 <= val && val <= 122)
    {
      dec = x;
      while (dec > 26)
        dec = dec - 26;
      hit = val + dec
      if (val >= 65 && val <= 90)
      {
        if (hit > 90)
          hit = hit - 26
      }
      if (97 <= val && val <= 122)
      {
        if (hit > 122)
          hit = hit - 26
      }
    }
    else
    {
      dec = x;
      while (dec > 10)
        dec = dec - 10;
      hit = val + dec
      if (hit > 57)
          hit = hit - 10

    }
    arr.push(hit)
  }
  ret = []
  for (let i =0; password.length > i; i++)
  {
    ret.push(String.fromCharCode(arr[i]))
  }
  str = ret.join('');
  return (swapCase(str))
};
