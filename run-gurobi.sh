make clean
make
for file in testes/*
do
  echo "========================================================================" >> gurobi-results.txt
  echo "========================================================================" >> gurobi-results.txt
  echo "==****************Executando arquivo: $file **************************==" >> gurobi-results.txt
  echo "========================================================================" >> gurobi-results.txt
  echo "========================================================================" >> gurobi-results.txt
  ./pmr -i "$file" -g -t 10 >> gurobi-results.txt
done
