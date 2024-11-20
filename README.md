# การติดตั้ง

ทำตามขั้นตอนด้านล่างเพื่อเริ่มใช้งานโปรเจค
เปิด cmd
1. Clone โปรเจคจาก GitHub
   ```bash
   git clone https://github.com/watcharin28/project_os.git
2. เข้าไปในโฟลเดอร์โปรเจค
   ```bash
   cd project_os
3. เปิดโปรเจคใน Visual Studio Code
    ```bash
    code .
4. run code ใน Visual Studio Code

# Project Scheduling Algolithms

## คุณสมบัติ
โปรแกรมรองรับอัลกอริธึมการจัดตารางการทำงานดังนี้

1. **First Come First Serve (FCFS)**  
2. **Round Robin (RR)**  
3. **Shortest Job First (SJF)**  
4. **Shortest Remaining Time First (SRTF)**  
5. **Priority Queue Scheduling**  
6. **Highest Response Ratio Next (HRRN)**  
7. **Multilevel Feedback Queue (MLFQ)**

# โปรแกรมจำลองการจัดตารางการทำงานของโปรเซส

## การใช้งาน

### ขั้นตอนที่ 1 เลือกอัลกอริธึม
โปรแกรมจะแสดงเมนูรายการอัลกอริธึมที่สามารถเลือกได้

- กดหมายเลขที่สอดคล้องกับอัลกอริธึมที่ต้องการ (1-7)
- ผู้ใช้สามารถเลือก หลายอัลกอริธึม ในโปรแกรมนี้ โดยการพิมพ์หมายเลขที่ต้องการ
- กด `-1` เมื่อเลือกเสร็จสิ้น
- โปรแกรมจะประมวลผลและแสดงผลลัพธ์สำหรับแต่ละอัลกอริธึมที่เลือกทั้งหมด
ตัวอย่าง
```plaintext
Select function that you want to simulate:
[1]  First come first serve
[2]  Round robin
[3]  Shortest job first
[4]  Shortest remaining time first
[5]  Priority queue
[6]  Highest response ratio next
[7]  Multilevel queue with feedback
[-1] Done
1
2
-1
   ```
        

### ขั้นตอนที่ 2 ป้อนจำนวนโปรเซส
- โปรแกรมจะถามจำนวนโปรเซสที่ต้องการจำลอง
  
ตัวอย่าง
 ```plaintext
How many processes:3
 ```
### ขั้นตอนที่ 3 ป้อนรายละเอียดโปรเซส
โปรแกรมจะถามรายละเอียดของแต่ละโปรเซส
- PID หมายเลขโปรเซส
- Arrival Time เวลาที่โปรเซสมาถึง
- Burst Time เวลาที่ใช้ในการทำงาน
  
ตัวอย่าง
```plaintext
Input process detail: ID, Arrival Time, Burst Time
1 0 5
2 1 3
3 2 8
```
### ขั้นตอนที่ 4 แสดงผลลัพธ์
โปรแกรมจะประมวลผลและแสดงผลลัพธ์ดังนี้
- Gantt Chart แสดงลำดับการทำงานของโปรเซส
  
รายละเอียดโปรเซส
- Waiting Time เวลาในการรอ
- Turnaround Time เวลารวมที่โปรเซสใช้
- Completion Time เวลาที่โปรเซสเสร็จสมบูรณ์

ค่าเฉลี่ย
- Average Waiting Time
- Average Turnaround Time
  
ตัวอย่างผลลัพธ์สำหรับ First Come First Serve (FCFS) และ Round robin (RR) เมื่อเลือกมาทั้ง 2 อัลกอริธึม
```plaintext
First Come First Serve Scheduling
Gantt Chart: | P1 | P2 | P3 |

Process Details:
PID     Arrival Time    Burst Time    Waiting Time    Turnaround Time
1       0               5             0               5
2       1               3             4               7
3       2               8             6               14

Average Waiting Time: 3.33
Average Turnaround Time: 8.67

------------------------------------------------------

Round Robin Scheduling
Gantt Chart: | P1 | P2 | P3 |

Process Details:
PID     Arrival Time    Burst Time    Waiting Time    Turnaround Time
1       0               5             0               5
2       1               3             4               7
3       2               8             6               14

Average Waiting Time: 3.33
Average Turnaround Time: 8.67

```
## คำแนะนำเพิ่มเติม
หากเลือกอัลกอริธึมอื่นๆ เช่น Round Robin, Priority Queue, หรือ Multilevel Feedback Queue โปรแกรมจะถามข้อมูลเพิ่มเติม เช่น

- Time Quantum (สำหรับ Round Robin)
- Priority (สำหรับ Priority Queue)
