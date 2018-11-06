# yuv_psnr
<p align="center">
Compare 2 YUV file and print PSNR throughtputs.
    <br><br><B>USAGE:<B><br>
    PROGRAM.exe   file1.yuv   file2.yuv   width      height     chroma_subsampling<br>
    </p>
 
<p align="center">
     
  <B>Program Açıklaması (Turkish)<B>
 <BR>
    Projede kullanılan YUV dosyaları, birçok YUV formatından biri olan 4:2:0 Chroma Subsampling’e sahip YV12 formatıdır. Bu formatta dosyanın memory adressing şekli aşağıda gösterdiğim gibi Y değerlerinin sonlanması ile ardına U (Cb) değerleri, Y değerlerinin  1/4  katı kadar uzunlukta devam eder. En son olarak V (Cr) değerleri de U değerleri boyu kadar adreslenir. Bu format biçimi her frame için tekrarlanır ve ardı ardına dosyaya yazılır.
    Proje kaynak kodlarındaki algoritma ise basit bir yapıdan oluşur. Programa yapılan 5 adet parametre girişi ile (1. Dosya, 2.Dosya, Genişlik, Yükseklik, Chroma Subsampling Modu) gerekli başlangıç değişkenleri alınır. Dosyanın yükseklik, genişlik ve sampling modu bilindiği için dosyanın kaç frame’den oluştuğunu da hesaplayabiliriz. Frame sayısı  FRAME SAYISI=(DOSYA BOYUTU)/(GENİŞLİK x YÜKSEKLİK x 1,5)  denklemi ile hesaplanır. (1.5 değeri girişte sampling modunun alınması ile belirlenen genişlik ve yükseklik değerleninin çarpılması ile hesaplanan 1x1’lik bir pikselin kaç byte’dan oluştuğunu belirtir. ) Daha sonra iki dosya da binary biçimde açılarak belirlenen buffer’lara aktarılır. Ardından her frame için buffer’lardan okunan Y,U,V piksel değerlerinin PSNR hesaplaması yapılarak ekrana çıktı verilir. En son olarak 2 dosyanın karşılaştırılan Y,U ve V değerlerinin ortalama PSNR oranları ekrana yazdırılır.

   <br><br>
  <img width="50%" height="auto" src="/images/2.jpg">
    
  <B>ORIGINAL FILE AND BLURRED FILE<B>
  <BR>
  <img width="50%" height="auto" src="/images/files_review.jpg">
  <BR>
  <B>PROGRAM THROUGHPUTS<B>
  <BR>
  <img width="50%" height="auto" src="/images/1.jpg">
  <img width="50%" height="auto" src="/images/2.jpg">
  
</p>
