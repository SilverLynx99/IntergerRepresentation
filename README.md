# IntergerRepresentation
Đồ án KTMT&amp;HN

Tao vừa mới merge và cập nhật lại các file của ae vào nhánh master.

## Giờ còn một số việc chúng ta phải làm. Cụ thể như thế này:
### Nhóm Nguyên + Nhân (Nhóm 1)**: Tập trung làm QFloat, không cần động tới QInt nữa. Nhân sẽ phân công cho Nguyên các công việc cần làm. Thứ 3 hoàn tất.
### Nhóm Nhân + Nhật + Phát (Nhóm 2): Tập trung làm QInt và xử lý file.

#### Cụ thể công việc nhóm 2
##### Nhật: Làm phép dịch trái, dịch phải, hàm nhân và chia (tao đã ghi sẵn prototype của hàm rồi, m tạo hàm ở file cpp để viết code).
##### Phát: Viết lại các hàm so sánh và gán. Tao đã viết sẵn prototype của hàm rồi và đã comment phần đó cho m rồi. M chỉ cần viết code thôi.
##### Tao: Viết các toán tử AND OR XOR NOT và check lại các hàm của ae.

## Cấu trúc project khi được tái thiết lại:
### Chúng ta có file main.cpp: Dùng để chạy chương trình chính.

### File QInt.h và QInt.cpp chứa các hàm của kiểu dữ liệu QInt và các hàm phụ trợ cho KDL này (được comment bằng cụm từ Utility Function)
### File Qfloat.h và Qfloat.cpp tương tự như trên.
### File UtilityFunc.h và .cpp chứa các hàm phụ trợ cho cả 2 file QInt.h và QFloat.

## Viết đúng hàm vào đúng cặp file. Không tự ý tạo file mới, sẽ rất khó để gộp chung vào.

## Cách dùng git từ giờ trở về sau:
### Chúng ta sẽ tạo một nhánh master (local) và thực hiện các thay đổi trên đó. Sau khi đã viết xong, thực hiện pull request để tham khảo ý kiến của người khác trước khi merge vào nhánh chính.

# Mong ae đọc ky code trước khi viết, việc gộp chung lại rất mệt và tốn thời gian. Cái gì k hiểu cứ inb hỏi t, chứ k nên tự viết.
