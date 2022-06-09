from MI import MI

mi = MI(3, "TVTri.lm", "HomoDictPoly+Tone.txt", False)
prob1 = mi.probSum("| zhong1 guo2 ren2 min2 sheng1 huo2 |")
prob2 = mi.probSum("| | zhong1 guo2 ren2 min2 | sheng1 huo2 |")
print(f"Prob1: {prob1} Prob2: {prob2}")