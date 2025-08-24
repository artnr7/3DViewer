# 3DViewer v2.0

Ushbu loyihada siz 3DViewer v2.0 dasturini ishlab chiqasiz.

💡 **Ushbu loyiha haqida biz bilan fikr-mulohazalaringizni baham ko’rish uchun [bu yerni bosing](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624).** Bu anonim bo’lib, jamoamizga ta’limni yaxshilashga yordam beradi. Loyihani tugatgandan so'ng darhol so'rovnomani to'ldirishni tavsiya qilamiz.

## Contents

  - [Chapter I](#chapter-i)
  - [Introduction](#introduction)
  - [Chapter II](#chapter-ii)
  - [Information](#information)
    - [Loyihalash patternlari](#loyihalash-patternlari)
  - [Chapter III](#chapter-iii)
  - [Part 1. 3DViewer v2.0](#part-1-3dviewer-v20)
  - [Part 2. Qo'shimcha. Sozlamalar](#part-2-qoshimcha-sozlamalar)
  - [Part 3. Qo'shimcha. Yozib olish](#part-3-qoshimcha-yozib-olish)

## Chapter I

![3dviewer2.0](misc/images/3dviewer2.0.PNG)

90-yillarda qahva mashinasi yaqinida:

*- Hammasi juda oddiy, do'stim. Bu bizga “Oskar” olib kelgan qisqa metrajli film kabi o'yinchoqlar haqidagi multfilm bo'ladi. O'yinchoqlarning dastlabki shakli low-ko'pburchakli 3D modellar uchun juda mos keladi, biz ularni animatsiyalashimiz mumkin. Tanqis mimikalar esa kritik bo'lmaydi, bular axir o'yinchoqlar-ku. Bizda esa allaqachon bir syujet bor... Ularni jonlantiramiz! Va o'yinchoqlar va bola o'rtasidagi munosabatlar haqida syujet tuzamiz.*

*- Tanish va jozibali eshitilyapti!*

*- Xuddi shunday. Siz imkon qadar tezroq jamoangizga borishingiz va 3D modellashtirish uchun dasturiy ta'minotni ishlab chiqishni boshlashingiz kerak. Agar ushbu multfilmni yaratmoqchi bo'lsak, bizga o'z dasturiy vositalarimiz kerak bo’ladi. Bozorda mavjud bo'lgan narsa faqat yog'och piramidani va hatto kub shaklida animatsiyalashga imkon beradi.*

*- Bilasizmi, menda ham xuddi shunday his bor. Qayerdadir hatto bir qancha tayyorlangan narsalar ham bor.*

*- Menimcha, biz asosiysidan – oldindan ko'rish ekranidan boshlashimiz kerak. Omad! - Bu so'zlar bilan Lasseter qahvasini ichib tugatib, krujkasini chaydi va sizni fikrlaringiz bilan yolg'iz qoldirib, dam olish xonasidan chiqib ketdi. U ketganidan keyin eshik sekin yopilib, tirqishlarida faqat tanish oq nur qoldi.*

*– Bir nechta renderlash strategiyalarini oldindan tayyorlab qo’ygan qulay bo'lardi... – deb o'ylagancha g'o'ldiradingiz siz baland ovozda. — Shuningdek, biznes mantigʻining barcha amalga oshirilishini qandaydir fasadning orqasida yashirish kerak, shunda UI bilan ishlash osonroq boʻladi. Va foydalanuvchi harakatlarini qayta ishlash uchun buyruqlarni ham, xo’sh-xo’sh ...*

To‘satdan olisdagi modemning dial-up ovozi sizni o‘ylaringizdan chalg‘itdi. Vazifani jamoa bilan muhokama qilish va kelajakdagi ilova arxitekturasini loyihalashni zudlik bilan amalga oshirish lozim. Vaqt kutib turmaydi!

Siz dam olish xonasining eshigini ochdingiz va yorqin nur yuzingizni to'ldirdi. Sizning qat'iyatingiz bukilmas, rejalashtirilgan multfilm esa tarixda qoladi! 

## Introduction

Ushbu loyihada siz C++ dasturlash tilida obyektga yo'naltirilgan dasturlash paradigmasida 3DViewer v1.0 loyihasida ilgari ishlab chiqilgan ilova bilan bir xil funksiyalarni amalga oshiruvchi karkas shaklida 3D modellarni ko'rish uchun ilovani amalga oshirishingiz kerak bo'ladi.

## Chapter II

## Information

### Loyihalash patternlari

Insonning har qanday faoliyatida, masalan, ovqat tayyorlash yoki yadro fizikasi sohasida tajribalar o'tkazishda, asosiy elementar vazifalarni hal qiladigan ma'lum bir o'rnatilgan amaliyotlar to'plami mavjud. Ular individual yondashuvni talab qilmaydi va odatda oldingi oshpazlar yoki yadro fiziklarining allaqachon to'plangan tajribasiga asoslangan uzoq vaqtdan beri mavjud yondashuvlar bilan hal qilinadi. Masalan, pirog pishirish uchun, hatto g'ayrioddiy bo'lsa ham, sizga pishirish texnologiyasi oldindan ma'lum bo'lgan va odatda ijodiy yondashuvni talab qilmaydigan xamir kerak bo'ladi. Dasturlash bilan ham xuddi shunday – loyihalashda sizdan oldin juda ko'p sonli dasturchilar duch kelgan oddiy vazifalar tez-tez uchrab turadi va ularning birgalikdagi tajribasi loyihalash patternlarini yaratdi.

**Loyihalash patterni** ilovani loyihalashda tez-tez takrorlanadigan vazifani va ushbu vazifa uchun universal bo'lgan uni hal qilish prinsipini tavsiflaydi. Ya'ni, dasturchi uchun loyihalash patterni –qurilish bloki, loyiha doirasida odatiy kichik vazifa paydo bo'lganda amalga oshiriladigan elementar birlikdan boshqa narsa emas.

Odatda, loyihalash patternlari uch guruhga bo'linadi: sababchi patternlar, tuzilmaviy patternlar va xatti-harakat patternlari. Loyihalash patternlari haqida ko'proq ma'lumot olish uchun ushbu topshiriq materiallariga qarang.

U yoki bu shakldagi MVC patterni foydalanuvchi interfeysiga ega ilovalarni ishlab chiqishda kodni tuzilmalashtirish nuqtai nazaridan eng keng tarqalgan yechimlardan biridir. Foydalanuvchi interfeysi va unga yondosh kontrollerga ega biznes-mantiq odatda ikkita turli global domenlarga bo'linadi: interfeys domeni va biznes-mantiq domeni.

Interfeys domeni faqat interfeysni aks ettirish va buyruqlarni biznes-mantiq domeniga o'tkazish uchun javob beradi. Fayldan yuklangan ma'lumotlar interfeys domenida saqlanmasligi kerak.

Tizimning asosiy funksionalligi uchun biznes-mantiq domeni javob beradi. Aynan shunda yuklab olingan ma'lumotlar saqlanadi va undagi barcha operatsiyalar bajariladi. Renderlash ham ushbu domenda amalga oshiriladi.

Biznes-mantiq domeni uchun taklif qilingan sinf diagrammasining namunasini materiallarda topishingiz mumkin.


## Chapter III

## Part 1. 3DViewer v2.0

Uch o'lchovli fazoda karkas modelini vizualizatsiya qilish dasturini ishlab chiqing.

- Dastur C++20 standarti C++ tilida ishlab chiqilgan bo'lishi kerak.
- Dastur kodi src papkasida bo'lishi kerak.
- Kod yozishda Google Stylega amal qilinishi kerak.
- Dastur to’plami GNU dasturlari uchun standart maqsadlar to'plamiga ega bo'lgan Makefile yordamida tuzilishi kerak: all, install, uninstall, clean, dvi, dist, tests. O'rnatish boshqa har qanday ixtiyoriy katalogda amalga oshirilishi kerak.
- Dastur obyektga yo'naltirilgan dasturlash prinsiplariga muvofiq ishlab chiqilishi kerak, tizimli yondashuv taqiqlanadi;
- Modelni yuklash va affin transformatsiyalari bilan bog'liq modullarning to'liq unit-testlar bilan qamrab olishi ta'minlanishi kerak.
- Ekranda bir vaqtning o'zida faqat bitta model bo'lishi kerak.
- Dastur quyidagi imkoniyatlarni taqdim etishi kerak:
    - obj formatdagi fayldan karkas modelini yuklash (faqat cho'qqilar va yuzalar ro'yxatini qo'llab-quvvatlash);
    - Modelni X, Y, Z o'qlariga nisbatan belgilangan masofaga o'tkazing;
    - Modelni X, Y, Z o'qlariga nisbatan ma'lum burchak ostida aylantirish;
    - Modelni berilgan qiymat bo'yicha masshtablash.
- Dasturda C++ uchun API ga ega bo’lgan har qanday GUI kutubxonasiga asoslangan grafik foydalanuvchi interfeysi amalga oshirilishi kerak:
  * Linux uchun: GTK+, CEF, Qt, JUCE;
  * Mac uchun: GTK+, CEF, Qt, JUCE, SFML, Nanogui, Nngui.
- Grafik foydalanuvchi interfeysi quyidagilarni o'z ichiga olishi kerak:
    - Modelga ega faylni tanlash tugmasi va uning nomini ko'rsatish uchun maydon;
    - Karkas modelini vizualizatsiya qilish zonasi;
    - Modelni ko'chirish uchun tugma/tugmalar va kiritish maydonlari;
    - Modelni aylantirish uchun tugma/tugmalar va kiritish maydonlari;
    - Modelni masshtablash uchun tugma/tugmalar va kiritish maydonlari;
    - Yuklangan model haqida ma'lumot – fayl nomi, uchlari va qirralari soni.
- Dastur to'g'ri ishlov berishi va foydalanuvchiga 100,1000,10,000,100,000,1,000,000 uchgacha bo'lgan detallarga ega modellarni muallaq turmasdan ko'rish imkonini berishi kerak (muallaq turish – interfeysning 0,5 soniyadan ko'proq vaqt davomida harakatsizligi).
- Dastur MVC patterni yordamida amalga oshirilishi kerak, ya'ni:
    - ko'rinish kodida biznes-mantiq kodi bo'lmasligi kerak;
    - kontroller va modelda interfeys kodi bo'lmasligi kerak;
    - kontrollerlar ingichka bo'lishi kerak.
- Kamida uchta turli xildagi loyihalash patternlaridan (masalan, fasad, strategiya va buyruq) foydalanish kerak.
- Sinflar `s21` nomli maydon ichida amalga oshirilishi kerak
- Affin transformatsiyalarini amalga oshirish uchun oldingi loyiha s21_matrix+ kutubxonasidagi matritsalardan foydalanish mumkin.

*Eslatma*: **“git”ga og'ir fayllarni (>10 MB) yuklamang.**

## Part 2. Qo'shimcha. Sozlamalar

- Dastur qirralarning turini (yaxlit, nuqtali), rangi va qalinligini, aks ettirish usulini (mavjud emas, doira, kvadrat), uchlarning rangi va o'lchamini sozlash imkonini berishi kerak.
- Dastur fon rangini tanlash imkonini berishi kerak.
- Sozlamalar dasturni qayta ishga tushirish oralig'ida saqlanishi kerak.

## Part 3. Qo'shimcha. Yozib olish
 
- Dastur olingan (“renderlangan”) tasvirlarni bmp va jpeg formatlarida faylga saqlash imkonini berishi kerak.
- Dastur kichik “skrinkastlarni” – yuklangan obyektning joriy foydalanuvchi affin transformatsiyalarni gif animatsiyasiga (640x480,10fps, 5s) yozib olish uchun maxsus tugmadan foydalanishga ruxsat berishi kerak.