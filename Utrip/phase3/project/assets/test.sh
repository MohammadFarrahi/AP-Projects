echo "________________Default_Price_filter____________"
for i in 1 2 3 4 5 6 7 8 9 10 11
do
    ./utrip.out hotels.csv ratings.csv < testcases/default_price_filter/"$i.in" > out.txt
    diff -w testcases/default_price_filter/"$i.out" out.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo   "\e[91mFail $i\e[0m"
    else
        echo   "\e[92mPass $i\e[0m"
    fi
done
echo "________________new_average_ratings_______________"
for i in 1 2 3
do
    ./utrip.out hotels.csv ratings.csv < testcases/new_average_ratings/"$i.in" > out.txt
    diff -w testcases/new_average_ratings/"$i.out" out.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo   "\e[91mFail $i\e[0m"
    else
        echo   "\e[92mPass $i\e[0m"
    fi
done
echo "_________________personal_rating____________________"
for i in 1 2 3 4 5 6 7 8 9 10
do
    ./utrip.out hotels.csv ratings.csv < testcases/personal_rating/"$i.in" > out.txt
    diff -w testcases/personal_rating/"$i.out" out.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo   "\e[91mFail $i\e[0m"
    else
        echo   "\e[92mPass $i\e[0m"
    fi
done
echo "__________________Default_Price_filter_________________"
for i in 1 2 3 4 5 6 7 8
do
    ./utrip.out hotels.csv ratings.csv < testcases/sort/"$i.in" > out.txt
    diff -w testcases/sort/"$i.out" out.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo   "\e[91mFail $i\e[0m"
    else
        echo   "\e[92mPass $i\e[0m"
    fi
done
echo "___________________weight_estimation_______________________"
for i in 1 2 3 4 5 6
do
    ./utrip.out hotels.csv ratings.csv < testcases/weight_estimation/"$i.in" > out.txt
    diff -w testcases/weight_estimation/"$i.out" out.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo   "\e[91mFail $i\e[0m"
    else
        echo   "\e[92mPass $i\e[0m"
    fi
done
