file_name="触手スーツ"

./get_pict_more
chmod +x get_pict.sh
mkdir /home/kaito/Pictures/$file_name
cp get_pict.sh /home/kaito/Pictures/$file_name
mv get_pict.sh /home/kaito/Pictures/$file_name
cd /home/kaito/Pictures/$file_name
./get_pict.sh
