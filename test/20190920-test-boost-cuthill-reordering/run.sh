
make

rm -rf *.dot *.png

echo ""
for exefile in $(ls *.exe)
do
    echo "run ${exefile}..."
    ./${exefile}
    echo ""
done

for g in $(ls *.dot | cut -d. -f1) 
do
    dot -Tpng ${g}.dot -o ${g}.png
done

