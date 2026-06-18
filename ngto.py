#*Tìm số nhỏ nhất trong 4 số 
import math

number_1 = int(input("Nhập số thứ nhất: "))
number_2 = int(input("Nhập số thứ hai: "))
number_3 = int(input("Nhập số thứ ba: "))
number_4 = int(input("Nhập số thứ tư: "))

min_number = min(number_1, number_2, number_3, number_4)
#Thêm là số thứ mấy nữaa
print("Số nhỏ nhất là:", min_number)
if min_number == number_1:
    print("Số nhỏ nhất là số thứ nhất.")
elif min_number == number_2:
    print("Số nhỏ nhất là số thứ hai.")
elif min_number == number_3:
    print("Số nhỏ nhất là số thứ ba.")
else:
    print("Số nhỏ nhất là số thứ tư.")
