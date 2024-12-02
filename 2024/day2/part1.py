with open("input.txt") as file:
    reports: list[list[int]] = [
        [int(n) for n in row.split(" ")]
        for row in file.read().splitlines()
    ]

safe = 0
for report in reports:
    failed = False
    increasing = report[1] > report[0]
    for last, level in zip(report, report[1:]):
        diff = level - last
        if abs(diff) not in [1,2,3]:
            failed = True
        if increasing and diff < 0 or not increasing and diff > 0:
            failed = True
    if not failed:
        safe += 1

print(safe)
