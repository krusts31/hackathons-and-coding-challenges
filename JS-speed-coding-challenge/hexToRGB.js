box.hexToRGB = function hexToRGB(x) {
  // x is a string
  // x is a string
  // return an array
  // (ex. x="#FFFFFF", you should return [255, 255, 255])

    ret = []
        if(x.length== 4){
            x= '#'+[x[1], x[1], x[2], x[2], x[3], x[3]].join('');
        }
        var c= '0x'+x.substring(1);
        ret.push((c>>16)&255)
        ret.push((c>>8)&255)
        ret.push(c&255);
        return (ret)
    
};
