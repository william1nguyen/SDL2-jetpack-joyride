# Jetpack

Nguyễn Việt Anh 21020001 K66CCLC

Game: Jetpack joyride

Nội dung game : Né các chướng ngại vật và chạy được càng lâu càng tốt

Video demo: 
https://drive.google.com/file/d/14CmS4Gn666EB7c7w9fSZVti58MEKZcJZ/view?usp=sharing

Công nghệ sử dụng :
- IDE: Codeblocks 20.03
- Thư viện : SDL2 SDL2_image SDL2_ttf SDL2_mixer

Cách chơi: 
Dùng các phím tắt:
- space : dùng để nhảy tránh chướng ngại vật
- p : dừng trò chơi lại, mọi trạng thái vẫn được lưu
- c : để tiếp tục trò chơi sau khi dừng
- r : để bắt đầu trò chơi lại từ đầu (restart) 
- q : để thoát khỏi trò chơi

thuật toán: 
- check 2 hình chữ nhật có giao nhau không (không thể dùng hàm trong SDL do còn nhiều sai số khi load ảnh) : hình chữ nhật có đỉnh trên cùng bên phải là (a_i, b_i) chiều rộng w_i, chiều dài h_i, nếu 2 hình chữ nhật giao nhau thì min(a_1, a_2) > max(b_1, b_2) + x, min(a_1 + w_1, a_2 + w_2) < max(b_1 + h_1, b_2 + h_2) + y. Trong đó x, y là sai số hình ảnh
- Zapper : lưu 3 trạng thái của zapper trong 1 vector pair là hình dạng của nó. x = WINDOW_WIDTH - w + id * w (id là số thứ tự để tránh trùng lặp, y = random.
- background : (có chuyển cảnh) load các ảnh back ground tại các vị trí first_x, first_x + image_width, first_x + 2 * image_width, ..., first_x sẽ giảm dần theo velocity của game, đồng thời first_x % tổng(image_width) để quay lại map đầu tiên.
