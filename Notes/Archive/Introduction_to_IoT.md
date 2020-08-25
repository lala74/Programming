# Giới thiệu về  Hệ thống nhúng và IoT

## Hệ thống nhúng

### Hệ thống nhúng là gì ?

Là một hệ thống có **1 con chip**: xem như là 1 bộ não chính để xử lý mọi việc mà chúng ta yêu cầu + **1 chương trình** chúng ta viết ra những yêu cầu của mình rồi nạp vào con chip.

Có thể xem cái máy laptop cũng là một hệ thống nhúng, **con chip** là mấy con chip Intel I3 I4 đấy, còn **chương trình** vd như gắn con chuột vào, khi di chuyển con chuột thì con trỏ trong laptop cũng di chuyển theo, muốn làm được việc đó thì cũng cần 1 chương trình nhận tín hiệu từ con chuột.

Trong thực tế thì hệ thống làm trên những sản phẩm đơn giản hơn nhiều, yêu cầu của người dùng cũng đơn giản hơn.

Vd: tưởng tượng là mình muốn làm ra 1 cái điều hòa nha. Thì cái điều hòa có chức năng chính là làm lạnh tới 1 nhiệt độ cố định nào đó.
Muốn làm lạnh tới nhiệt độ cụ thể thì đầu tiên phải biết được nhiệt độ môi trường là bao nhiêu. Đối với con người thì mình cầm nhiệt kế để đọc, nhưng với máy thì khó có thể đọc được như con người, nên nhiệt độ môi trường được đo bằng 1 cảm biến đặc biệt xong rồi gửi cho **con chip** bằng các giao thức giao tiếp.

#### Con chip là gì ?

(tìm mấy ảnh con chip vất vô nhé)
![ví dụ](https://5.imimg.com/data5/YR/GM/MY-53933770/semiconductor-chip-500x500.jpg)

Con chip là mấy cái cục đen đen mà có 1 đống chân lòi ra ấy. Chỉ cần tưởng tượng con chip như 1 đứa nô lệ vậy, ví dụ như 1 con nô lệ nằm trong máy lạnh ấy, em biểu nó khi nào m thấy lạnh quá (cảm biến chỉ nhiệt độ thấp) thì m tắt máy lạnh đi. Chỉ cần hiểu như thế là ok

`chip = nô lệ`

#### Chương trình để nạp vào con chip là gì ?

Tưởng tượng tiếp là con nô lệ ni nói tiếng thượng mình k hiểu được, hắn chỉ hiểu tiếng anh phiên bản đơn giản thôi, do đó mình phải viết yêu cầu của mình một cách đơn giản nhất có thể cho nó hiểu được. Ví dụ nè :

```Pascal
if (nhiệt độ < 15 độ) then
    Tắt điều hòa
end if
```
`chương trình = mệnh lệnh của chủ giao cho nô lệ`

#### Hệ thống nhúng giúp gì cho cuộc sống ?

Thì như ví dụ ở trên, e có thể thấy là cuộc sống mà thiếu đi nô lệ để sai bảo thì mình phải làm hết tất cả. Do đó nô lệ càng nhiều thì cuộc sống càng nhàn, mục đích chính của hệ thống nhúng cũng là vậy :
> Giúp con người không tốn thời gian + sức lực vào làm những việc vô bổ  : tắt máy lạnh khi trời mát, lau nhà (robot lau nhà), giặt - gấp áo quần, lấy quần áo vào khi trời mưa,... (mấy việc mà ba mẹ hay sai làm ấy, master hệ thống nhúng thì khỏi cần làm mấy cái đó :*)

#### Hệ thống nhúng có bị lỗi thời không ?

Bao giờ con người k cần nô lệ nữa thì lúc đó hệ thống nhúng mới lỗi thời, suy ra méo bao giờ lỗi thời được do con người ngày càng nhác nên càng muốn nhiều nô lệ phục vụ cho mình thôi :*

#### Vì sao mình chọn hệ thống nhúng ?

Vì từ lâu mình đã thích cảm giác được điều khiển cái gì đó, kiểu có 1 thứ nó phục vụ hoàn toàn mọi mệnh lệnh mình đưa ra ấy. Nên từ nhỏ mình đã thích mấy xe điều khiển rồi mấy thứ công nghệ cao trên tv \m/

Mà chỉ chơi đồ điều khiển k thì k có sướng nên mình quyết định phải học sao để tự tạo ra nô lệ cho mình luôn thì mới được (mỗi người 1 nhu cầu riêng nên phải có nô lệ riêng thôi)

## IoT

### IoT là gì ?

Iot là viết tắt của Internet Of Things, hiểu một cách đơn giản là mọi thứ đều được kết nối với nhau bằng Internet. Như ví dụ ở trên thì em thấy con nô lệ của mình nó nằm trong máy điều hòa ấy, muốn đưa ra mệnh lệnh thì mình phải tới nói thẳng mặt nó để giao việc. Nhưng giả sử bây giờ em đang đi làm ở một nơi xa, thì lúc đó làm sao để có thể nói chuyện với nó được đúng không, lúc đó thì mình phải viết thư rồi nhờ bồ câu đưa tới con nô lệ thôi. Thì bồ câu ở đây là mạng Internet đấy. Chừ có bồ câu rồi thì em ở bất cứ đâu cũng có thể ra lệnh cho con nô lệ của mình được \m/

**Thực tế :** Giả sử bây giờ mình có 1 cái trường có 100 phòng học nha, mong ước của mình là phòng nào không có người thì tắt đèn đi cho tiết kiệm điện và mình cũng muốn biết hiện tại phòng nào không có người rồi thông báo cho những học sinh đang tìm phòng trống để học nhóm. Về phần tắt điện thì mình chỉ cần nói con nô lệ là *"ê m khi mô k chộ người trong phòng thì tắt điện hộ t cái nha"*. Nhưng mà để biết được hiện tại phòng nào đang trống thì mình phải tự thân đi check, cứ chạy vòng vòng cả 100 phòng vậy để biết phòng nào có người hay k. Lúc đó IoT mới phát huy tác dụng, cứ 1 phút thì con nô lệ sẽ gửi bồ câu về tình trạng phòng cho mình, do đó cứ mỗi 1 phút thì học sinh sẽ được cập nhật tình trạng phòng một lần. Tiện hơn chạy đi chạy về nhiều phải không ? 

`Internet = bồ câu`

### Lợi ích của IoT ?

1. Xóa nhòa khoảng cách giữa nô lệ và chủ cho dù 2 bên có cách xa nhau bao nhiêu. Chỉ cần có chim (bồ câu) là có thể giao tiếp được với nhau rồi.
2. Điều khiển được nhiều nô lệ cùng lúc, do không phải chạy đi chạy về giữa các con nô lệ mà chỉ cần ngồi 1 chỗ xử lý do đó số lượng nô lệ tăng theo khả năng xử lý của mình. Xử lý càng nhanh thì càng nuôi được nhiều nô lệ.
3. Quản lý nô lệ dễ dàng hơn do tất cả thông tin đều được đưa về 1 nơi để xử lý

## Ví dụ thực tế

Mình đang làm thực tập cho một công ty công nghệ thông tin, chủ đề thực tập là : **phát triển hệ thống cảm biến phát hiện xe hơi tiêu thụ năng lượng thấp cho các bãi đỗ xe thông minh**

### Giới thiệu về chủ đề thực tập

Ở ví dụ này thì thay vì con nô lệ ngồi trên trần nhà để điều khiển máy lạnh thì bây giờ nó nằm giữa chỗ đậu xe ấy đề báo cho mình biết cái chỗ đó đã có xe hay chưa.

### Công việc chính :

**Dạy con nô lệ cách phát hiện xe hơi** (do con nô lệ này bị mù với cả điếc nữa, hắn cảm nhận xe hơi bằng giác quan thứ 6 (từ trường) nên phải dạy tốt nó mới phát hiện được (p/s: không phải machine learning gì đâu nha).

**Dạy nô lệ cách gửi bồ câu** loại bồ câu được sử dụng trong đề tài là Bluetooth nên phải tìm cách để có thể giao tiếp với nhau bằng Bluetooth - như tìm cách để con bồ câu ni bay được ấy.

**Xử lý dữ liệu từ con bồ câu mà nô lệ gửi đến** do một bãi đỗ xe thì có đến cả trăm chỗ đậu, mỗi con nô lệ lại gửi bồ câu mỗi khi có xe đến/xe đi nên nếu mình không tìm cách để xử lý thì sẽ có lúc bị quá tải ngay

**Đưa dữ liệu đó đến người dùng** thì con bồ câu mang thông tin được viết bằng tiếng thượng thì mình phải dịch nó qua tiếng kinh rồi gửi nó cho người dùng thôi - bằng app Android + gửi bằng Wifi/3G

## Chuẩn bị gì để học tốt hệ thống nhúng + IoT ?

### Tiếng anh

Cần tiếng anh **đọc hiểu** tốt + kĩ năng **nghe** tốt (chủ yếu kĩ năng bị động thui) là đủ.

**Nghe tốt** là vì nhiều lúc phải mua các khóa học trên mạng do ở trường thì không thể nào dạy hết mọi thứ cho các em được. Trường đại học chỉ dạy e kĩ năng tự học thôi =)) Mà nên mua các khóa học tiếng anh (Udemy,...) vì các khóa học đó được nhiều người học rồi, được đánh giá cao + họ có chương trình dạy bài bản từ đầu. Chứ mới vô mà coi youtube để tự học thì dễ bị loạn lắm.

**Đọc hiểu tốt** là vì phải đọc datasheet(éo biết tiếng việt gọi là gì -_-) để có thể hiểu được con chip hoạt động kiểu gì (kiểu như học văn hóa của cái đứa nô lệ ấy để ra lệnh cho nó cho đúng). Mà datasheet thì toàn viết bằng tiếng anh thôi nên là k biết tiếng anh thì xác định sấp mặt =))

### Tự học

Như đã nói ở trên là trường đảm bảo sẽ k dạy chi tiết được nên việc mua khóa học là gần như bắt buộc rồi. Với lúc đi thực tập hay đi làm thì khi có vấn đề cũng k có ai giúp cả, phải tự lên mạng tìm rồi sửa thô.

### Đam mê

Chỉ cần thích cảm giác một mình điều khiển được mọi thứ là OK rồi :*

##### Author: La Minh Đức <3

