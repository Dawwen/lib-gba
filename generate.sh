# Remove old headers
rm -f header/*.hpp
# Generate new headers
dia2code -t cpp -d info/generated info/SubaruNew.dia
# Fix them
python3 info/generate.py
# Move them to the right folder
mv info/generated/* header
