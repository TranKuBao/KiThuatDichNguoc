# Basic API Hooking

Chào tất cả anh em!!!
Hôm này mình vừa học sơ qua phần API_Hooking nên mình sẽ viết lại và demo!! Ae có gì thấy sai thiếu nhớ và comment nhá!!

Đầu Tiên là mình sẽ trình bày sơ qua về phần API trong phần Kĩ thuật dịch ngược.

## API là gì

Hàm API (Application Programming Interface) là các hàm được cung cấp bởi hệ điều hành hoặc thư viện phần mềm để cho phép các ứng dụng thực hiện các chức năng nhất định, từ giao tiếp với phần cứng đến thực hiện các thao tác xử lý dữ liệu. Dưới đây là một số nhóm hàm API phổ biến, đặc biệt là trong hệ điều hành Windows, nơi các hàm API thường được sử dụng trong lập trình hệ thống và ứng dụng:

*  **Hàm API Xử lý Tệp tin (File I/O APIs):** Dùng để thao tác với tệp tin và thư mục như tạo, đọc, ghi, hoặc xóa.	
    - CreateFile(): Mở hoặc tạo một tệp tin hoặc thiết bị.
    -  ReadFile(), WriteFile(): Đọc hoặc ghi dữ liệu vào tệp.
    -  DeleteFile(): Xóa một tệp tin.
    -  CopyFile(), MoveFile(): Sao chép hoặc di chuyển tệp tin.
* **Hàm API Quản lý Bộ nhớ (Memory Management APIs):**	Cung cấp các thao tác quản lý bộ nhớ, như cấp phát hoặc giải phóng bộ nhớ.
	-  VirtualAlloc(), VirtualFree(): Cấp phát và giải phóng vùng nhớ.
    - GlobalAlloc(), GlobalFree(): Cấp phát và giải phóng bộ nhớ toàn cục.

* **Hàm API Xử lý Quy trình và Luồng (Process and Thread Management APIs):** Được sử dụng để tạo và quản lý các quy trình (process) và luồng (thread).	
     -  CreateProcess(): Tạo một quy trình mới.
     -  CreateThread(): Tạo một luồng mới.
     -  TerminateProcess(): Kết thúc một quy trình.
     -  WaitForSingleObject(): Chờ một quy trình hoặc luồng hoàn thành.
     
* **Hàm API Quản lý Registry (Registry APIs):**	Cho phép thao tác với Windows Registry, hệ thống cơ sở dữ liệu để lưu trữ cấu hình hệ thống và ứng dụng.	
    -  RegOpenKeyEx(): Mở một khóa trong Registry.
    -  RegSetValueEx(): Thiết lập giá trị cho một khóa Registry.
    -  RegDeleteKey(), RegDeleteValue(): Xóa khóa hoặc giá trị trong Registry.
    
* **Hàm API Giao tiếp Mạng (Networking APIs):**	Hỗ trợ các thao tác giao tiếp mạng, bao gồm kết nối internet, gửi/nhận dữ liệu qua mạng.	

* **Hàm API Xử lý Cửa sổ và Thao tác Giao diện (Window and User Interface APIs):** Dùng để tạo, quản lý và tương tác với các cửa sổ giao diện người dùng.	
    -  CreateWindowEx(): Tạo một cửa sổ mới.
    -  ShowWindow(), UpdateWindow(): Hiển thị và cập nhật cửa sổ.
    -  GetMessage(), DispatchMessage(): Xử lý thông điệp từ hệ thống.
    -  MessageBox(): Hiển thị hộp thoại thông báo.

* Nói chung là nhiều đấy, thích thì cứ lên mạng mà search hay hỏi tk GPT ấy. Được rồi nói chung nói thế để ae biết API mà mình muốn nói là cái gì thôi*

## API HOOKING
   API mà mình muốn đề cập đây là trong phần kĩ thuật dịch ngược nhé.
   Trong kỹ thuật phân tích dịch ngược, API Hooking là một phương pháp giúp người phân tích hoặc nhà phát triển có thể "chen ngang" và can thiệp vào quá trình gọi hàm API trong một ứng dụng hoặc hệ thống. Điều này cho phép họ theo dõi, kiểm soát hoặc thay đổi hành vi của các hàm API mà ứng dụng sử dụng. 
 ### Vậy API HOOKING nso thường được sử dụng để làm gì???
-	Theo dõi các hàm API mà ứng dụng gọi để hiểu luồng hoạt động của nó.
-	Phân tích mã độc bằng cách giám sát các API liên quan đến hệ thống file, registry, và mạng để hiểu hành vi của mã độc.
-	Kiểm tra bảo mật và bảo vệ hệ thống bằng cách ngăn chặn các hành động không mong muốn hoặc gian lận.
-	Thay đổi hành vi của các ứng dụng bằng cách điều chỉnh đầu vào/đầu ra của các hàm API.

### Vậy có những loại API HOOKING nào?
API Hooking có thể được thực hiện bằng nhiều kỹ thuật khác nhau, tùy thuộc vào cách mà lập trình viên muốn can thiệp vào quá trình gọi API. Dưới đây là các loại API Hooking chính:
#### 1. Inline Hooking
•	Cách thức hoạt động: Inline Hooking thay đổi mã nguồn của hàm API trực tiếp trong bộ nhớ. Điều này được thực hiện bằng cách sửa đổi một số byte đầu tiên của hàm API để chuyển hướng nó đến hàm tùy chỉnh (custom function).
•	Ưu điểm: Đơn giản và hiệu quả, ít ảnh hưởng đến hiệu suất.
•	Nhược điểm: Phụ thuộc vào kiến trúc CPU, dễ bị phát hiện bởi các phần mềm chống gian lận hoặc phần mềm bảo mật.
•	Ứng dụng: Phổ biến trong các phần mềm phân tích mã độc hoặc điều tra hành vi của chương trình.
#### 2. Import Address Table (IAT) Hooking
•	Cách thức hoạt động: IAT Hooking thay đổi địa chỉ hàm trong bảng IAT của một module, nơi lưu trữ địa chỉ của các hàm API được ứng dụng gọi đến. Khi ứng dụng cố gắng gọi API, nó sẽ được chuyển hướng đến hàm tùy chỉnh.
•	Ưu điểm: Không cần thay đổi mã nguồn của hàm API, dễ triển khai.
•	Nhược điểm: Chỉ hiệu quả khi ứng dụng sử dụng bảng IAT để tra cứu hàm API; dễ bị phát hiện.
•	Ứng dụng: Theo dõi các API được gọi trong ứng dụng, đặc biệt trong các ứng dụng Windows.
#### 3. Export Address Table (EAT) Hooking
•	Cách thức hoạt động: EAT Hooking can thiệp vào bảng EAT của DLL để thay đổi địa chỉ các hàm API ngay tại nơi export của thư viện, không chỉ ảnh hưởng đến một module mà đến tất cả các module sử dụng API từ thư viện đó.
•	Ưu điểm: Có phạm vi rộng hơn IAT Hooking; hữu dụng khi ứng dụng gọi trực tiếp hàm từ DLL.
•	Nhược điểm: Khó triển khai hơn IAT Hooking và có thể gây ra lỗi ngoài ý muốn cho các module khác.
•	Ứng dụng: Theo dõi hoặc ngăn chặn các API trên toàn hệ thống, ví dụ như kiểm tra việc sử dụng các API mạng hoặc file.
#### 4. Virtual Table (VTable) Hooking
•	Cách thức hoạt động: Được sử dụng với các đối tượng trong lập trình hướng đối tượng, VTable Hooking thay đổi địa chỉ hàm trong bảng hàm ảo (vtable) của một đối tượng để chuyển hướng các cuộc gọi đến hàm khác.
•	Ưu điểm: Rất hữu dụng khi làm việc với các đối tượng COM trong Windows.
•	Nhược điểm: Giới hạn trong các đối tượng có VTable, chủ yếu trong các ngôn ngữ hướng đối tượng như C++.
•	Ứng dụng: Thường dùng trong các ứng dụng Windows có sử dụng đối tượng COM.
#### 5. Detour Hooking
•	Cách thức hoạt động: Detour Hooking chèn mã để chuyển hướng luồng điều khiển của một hàm API đến hàm tùy chỉnh, rồi từ đó có thể gọi API gốc hoặc thực hiện các tác vụ khác.
•	Ưu điểm: Phổ biến và hiệu quả cao, Detours Library của Microsoft là một trong những thư viện thực hiện detour phổ biến nhất.
•	Nhược điểm: Có thể ảnh hưởng đến hiệu suất nếu không được triển khai đúng cách.
•	Ứng dụng: Thường dùng để giám sát hoặc thay đổi hành vi của các API hệ thống.

## Demo thử cho ae dễ hiểu :)))
Mình sẽ viết 1 cái code kiểm tra password. 
![image](https://hackmd.io/_uploads/Hy-ppOJG1l.png)

Nếu đầu vào là bội chung của của 12 và 20 thì sẽ hiển thị messagebox bảo là mày đã đăng nhập thành công. Ngược lại thì éo.

![image](https://hackmd.io/_uploads/rkMQ0d1Gkg.png)

![image](https://hackmd.io/_uploads/rJYrRu1fyg.png)

OK!! Trình bày sương sương thế để cho các bạn dễ hiểu.
Bây giờ với phải biên dịch mình sẽ tiến hành reverse xem, để tìm ra được địa chỉ của các function()

**Ở đây mình sẽ sử dụng x32-x64dbg**
Đâu tiên mình tìm **uesr32.dll** để mò ra địa chỉ **MessageBoxA** là *0x7760ADC0* 
![image](https://hackmd.io/_uploads/S16O1t1fyl.png)

Rất khó để có thể xác định được nơi chương trình mính bắt đâu, nến tôi sẽ tìm kiếm theo string *“Enter”* để nhảy đến vị trí của thằng main(). Sau đó tôi cũng xác định vị trí các điểm nhảy và lệnh call các fuction() trong Hàm MAIN
![image](https://hackmd.io/_uploads/r1_TytJMkl.png)

Sau đó mình sẽ tiếp tục tìm chỗ **checkpass()** với điểm chỉ bắt đầu là *0x00401460*
![image](https://hackmd.io/_uploads/ry_lxK1fJx.png)

Chúng ta sẽ thấy các chỗ tô vàng sẽ là các điểm nhảy với điệu kiện **Switch case**:
![image](https://hackmd.io/_uploads/BJmMgY1Myl.png)

Tôi cũng xác định luôn được 2 function gọi messagebox kết quả *đúng* hoặc *sai* :
![image](https://hackmd.io/_uploads/S1pnxKyzJg.png)

Nãy giờ ae đọc chắc thấy chán nhỉ nhưng có mục đích cả bạn ơi. 
Bây giờ mình sẽ demo theo kiểu Inline Hooking, **nghĩa là mình sẽ can thiệp trực tiếp vào mã nguồn của một hàm API (hoặc bất kỳ hàm nào) trong bộ nhớ. Thông qua việc chỉnh sửa các byte đầu tiên của hàm, chúng ta có thể chuyển hướng chương trình đến một hàm khác (hàm tùy chỉnh) để thực hiện thao tác mong muốn. Sau khi hoàn thành, nếu cần, có thể quay lại hàm gốc để tiếp tục.**

### Cách thức hoạt động của Inline Hooking
- Ghi đè một số byte đầu tiên của hàm API (thường là 5 byte) bằng một lệnh nhảy (JMP) hoặc gọi (CALL) để chuyển hướng đến hàm tùy chỉnh.
- Thực thi hàm tùy chỉnh: Hàm này có thể thực hiện các thao tác cần thiết, như ghi log hoặc kiểm tra, rồi gọi lại hàm gốc nếu cần.
- Quay trở lại hàm gốc: Nếu mục đích chỉ là can thiệp một phần, hàm tùy chỉnh có thể gọi lại hàm gốc sau khi hoàn thành công việc của nó.
![image](https://hackmd.io/_uploads/HJc9zYkGke.png)

Và ở trên tôi đã ghi lại địa chỉ của fucntion checkpass() và các hàm quan trọng với mục đích:
1.	Nhảy đến đẩu fucntion checkpass()
2.	Thay đổi mà sửa thành 1 lệnh JMP xxxxxxxnx
3.	Tại địa chỉ xxxxxxxnx thì là địa chỉ nơi không có code, nên tôi sẽ viết 1 đoạn ASM để hiển thị messageBOX rằng tôi đã “cái ứng dụng này đã bị hack”
4.	Tiến hành làm. 

Đây là chỗ fuction hiển thị messageBox và tôi dựng lại sẽ thêm 1 đoạn code mới tương tự nhưng với địa chỉ khác.
![image](https://hackmd.io/_uploads/HkbuXtkGkg.png)

Đầu tiên thêm 1 các segment, nên nhớ là phải thêm quyền cho nó:
![Có nhiều cách để thêm tùy anh thêm bằng segm bằng các gì nhé!! ](https://hackmd.io/_uploads/Bkz9XFyGyx.png)

Ở đâu mình sẽ thêm 2 các chuỗi để gán lên cái messageboxA kia(*Cái này thằng bạn trong phòng chỉ :))))* : ![image](https://hackmd.io/_uploads/rJwi4KkfJe.png)

Bắt đầu thêm code tại địa chỉ: *0x00411000* tại segment mới VÀ mình gọi đây là hàm **HookedMessageBoxA**
![image](https://hackmd.io/_uploads/rkKHrF1GJl.png)

### Giải thích chi tiết hơn 1 tí 
- Khi nhảy đến hàm **CheckPass** thì nó sẽ không kiểm tra pass, mà ở đây tôi đã thay bằng 1 lệnh JMp để nhảy đến **HookedMessageBoxA** 
![image](https://hackmd.io/_uploads/HyQsLYJMyx.png)

Trong hàm **HookedMessageBoxA** khi thông báo xong messagebox thì sẽ nhảy ngược về chỗ hàm thông báo đăng nhập thành công để kết thúc chương trình.
![image](https://hackmd.io/_uploads/HyCALK1z1g.png)

##Kết quả
Nghĩa là cho dù mình nhập cái gì cũng bỏ qua phần checkpass và thông báo phần mềm bị hack
![image](https://hackmd.io/_uploads/SkrIuFyfyx.png)

và cuối cùng là hiển thị thông báo thành công
![image](https://hackmd.io/_uploads/Byr5_FkGJx.png)

--Hết-- 
Ở trên là phần mình tìm hiểu, có gì mong mọi người đóng góp thêm cho mình.

*Mình để đường dẫn ở đây, ae thích có thể pull code về chạy thử:* [\$_MlemKem\_\$'](https://github.com/TranKuBao/KiThuatDichNguoc/tree/main/ApiHook_Loader/API_)
*Reference:* 
+ https://www.youtube.com/watch?v=SA96PakHrrE
+ https://medium.com/geekculture/basic-windows-api-hooking-acb8d275e9b8
+ [Hoặc không biết thì có thể gọi cho thằng đệ mình :)))](chatgpt.com)

