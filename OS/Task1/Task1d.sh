c="wow"
one="1"

for file in c*
do cp "$file" "$c$one"
c=$c$one
done
