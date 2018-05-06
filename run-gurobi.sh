make clean
make
for file in testes/*
do
  echo "Executando arquivo: $file"  >> gurobi-results.txt
  ./pmr -i "$file" -g -t 10 >> output.txt
done
