cd build

echo "+-------------------+"
echo "| building makefile |"
echo "+-------------------+"
cmake CMakeLists.txt .
if [ $? -ne 0 ]; then
  echo "+------------------------------------+"
  echo "| Error building makefile. Aborting. |"
  echo "+------------------------------------+"
  exit
else
  echo "+-----------------------------+"
  echo "| makefile built successfully |"
  echo "+-----------------------------+"
fi

echo ""

echo "+------------------+"
echo "| building project |"
echo "+------------------+"
make
if [ $? -ne 0 ]; then
  echo "+-----------------------------------+"
  echo "| Error building project. Aborting. |"
  echo "+-----------------------------------+"
  exit
else
  echo "+----------------------------+"
  echo "| project built successfully |"
  echo "+----------------------------+"
fi
echo ""

echo "+-----------+"
echo "| executing |"
echo "+-----------+"
./star
result=$?
if [ $result -ne 0 ]; then
  echo "+-------------------------------------+"
  echo "| program quit abnormally with code $result |"
  echo "+-------------------------------------+"
  exit
else
  echo "+---------------------------+"
  echo "| program quit successfully |"
  echo "+---------------------------+"
fi
