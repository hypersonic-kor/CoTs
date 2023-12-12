import tkinter as tk
from datetime import datetime, timedelta

# 각 지역의 UTC 시차와 표준시
time_diff = {
    "서울": (9, "KST"),
    "워싱턴 DC": (-5, "EST"),
    "리스본": (0, "WET"),
    "호눌룰루": (-10, "HST"),
    "베이징": (8, "CST"),
    "타슈켄트": (5, "TJT"),
    "이슬라마바드": (5, "PKT"),
    "뉴델리": (5.5, "IST"),
    "하르툼": (3, "ART"),
    "방기": (1, "CET"),
    "마드리드": (1, "CET"),
    "누크": (1.5, "NST"),
    "뉴욕": (-4, "EDT"),
    "런던": (0, "GMT"),
    "파리": (1, "CET"),
    "도쿄": (9, "JST"),
    "시드니": (11, "AEDT"),
    "상파울루": (-3, "BRT"),
    "카이로": (2, "EET"),
    "모스크바": (3, "MSK"),
    "베를린": (1, "CET"),
    "상트페테르부르크": (3, "MSK"),
    "상하이": (8, "CST"),
    "홍콩": (8, "HKT"),
    "두바이": (4, "GST"),
    "멕시코 시티": (-5, "CDT"),
    "부에노스 아이레스": (-3, "ART"),
    "방콕": (7, "ICT"),
    "유럽/아프리카": (0, "GMT"),
    "태평양": (-8, "PST"),
    # 추가 도시와 시간대
}

# 시간을 가져오는 함수
def get_local_time(city):
    city_time_diff, city_standard_time = time_diff[city]
    current_time = datetime.utcnow() + timedelta(hours=city_time_diff)
    return current_time.strftime(f"{city_standard_time} (%Y) (%m) (%d) (%H) (%M) (%S)")

# tkinter 창 설정
root = tk.Tk()
root.title("세계 시간")

# 도시 목록 가져오기
cities = list(time_diff.keys())
labels = []

# 모든 도시의 현재 시간 표시
for idx, city in enumerate(cities):
    label_text = f"{city}: {get_local_time(city)}"
    label = tk.Label(root, text=label_text, font=("Arial", 9))
    label.grid(row=idx, column=0, padx=20, pady=5, sticky="w")
    labels.append(label)

# 시간 업데이트 함수
def update_times():
    for idx, city in enumerate(cities):
        labels[idx].config(text=f"{city}: {get_local_time(city)}")
    root.after(1000, update_times)

update_times()  # 시간 업데이트 시작

root.mainloop()
