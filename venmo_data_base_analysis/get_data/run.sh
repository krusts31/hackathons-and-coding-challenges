bash get_data.sh
make -C libft

make
./a.out 1 > files/get_note.sh 2> files/stats.txt
./a.out 2 > files/get_comment_one.sh
./a.out 3 > files/get_comment_two.sh

bash files/get_note.sh >> files/note_data.txt
bash files/get_comment_one.sh
bash files/get_comment_two.sh

cat files/comment_one_data.txt >> note_data.txt
cat files/comment_two_data.txt >> note_data.txt
rm files/comment_one_data.txt
rm files/comment_two_data.txt
