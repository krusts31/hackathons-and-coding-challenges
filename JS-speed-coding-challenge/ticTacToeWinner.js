box.ticTacToeWinner = function ticTacToeWinner(x) {
  let x_won = 0
  let o_won = 0
  if (x[0][0] == 'x' && x[0][1] == 'x' && x[0][2] == 'x')
    x_won = 1;
  if (x[1][0] == 'x' && x[1][1] == 'x' && x[1][2] == 'x')
    x_won = 1;
  if (x[2][0] == 'x' && x[2][1] == 'x' && x[2][2] == 'x')
    x_won = 1;

  if (x[0][0] == 'x' && x[1][0] == 'x' && x[2][0] == 'x')
    x_won = 1;
  if (x[0][1] == 'x' && x[1][1] == 'x' && x[2][1] == 'x')
    x_won = 1;
  if (x[0][2] == 'x' && x[1][2] == 'x' && x[2][2] == 'x')
    x_won = 1;

  if (x[0][0] == 'x' && x[1][1] == 'x' && x[2][2] == 'x')
    x_won = 1;
  if (x[0][2] == 'x' && x[1][1] == 'x' && x[2][0] == 'x')
    x_won = 1;

  if (x[0][0] == 'o' && x[0][1] == 'o' && x[0][2] == 'o')
    o_won = 1
  if (x[1][0] == 'o' && x[1][1] == 'o' && x[1][2] == 'o')
    o_won = 1
  if (x[2][0] == 'o' && x[2][1] == 'o' && x[2][2] == 'o')
    o_won = 1

  if (x[0][0] == 'o' && x[1][0] == 'o' && x[2][0] == 'o')
    o_won = 1
  if (x[0][1] == 'o' && x[1][1] == 'o' && x[2][1] == 'o')
    o_won = 1
  if (x[0][2] == 'o' && x[1][2] == 'o' && x[2][2] == 'o')
    o_won = 1

  if (x[0][0] == 'o' && x[1][1] == 'o' && x[2][2] == 'o')
    o_won = 1
  if (x[0][2] == 'o' && x[1][1] == 'o' && x[2][0] == 'o')
    o_won = 1
  if (o_won == 0 && x_won == 0)
    return ('draw')
  if (o_won == 1 && x_won == 1)
    return ('error')
  if (x_won)
    return ('x');
  if (o_won)
    return ('o');
};
