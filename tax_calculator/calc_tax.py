#!/bin/env python3



# 所得税
def _income_tax(val):
    """
    :val: 源泉徴収票の「給与所得控除後の金額」引く「所得控除の額の合計額」
    :returns: 源泉徴収票の「源泉徴収税額」
    """
    if 1000 <= val and val < 1949000:
        return val * 5 / 100.0
    if 1950000 <= val and val < 3299000:
        return val * 10 / 100.0 - 97500.000000
    if 3300000 <= val and val < 6949000:
        return val * 20 / 100.0 - 427500.000000
    if 6950000 <= val and val < 8999000:
        return val * 23 / 100.0 - 636000.000000
    if 9000000 <= val and val < 17999000:
        return val * 33 / 100.0 - 1536000.000000
    if 18000000 <= val and val < 39999000:
        return val * 40 / 100.0 - 2796000.000000
    if 40000000 <= val:
        return val * 45 / 100.0 - 4796000
def income_tax(val):
    return 1.021 * _income_tax(val) // 1000 * 1000

# 住民税
# https://www.city.yokohama.lg.jp/kurashi/koseki-zei-hoken/zeikin/kojin-shiminzei-kenminzei/kojin-shiminzei-shosai/kojin.html
def resident_tax(val):
    """
    :val: 源泉徴収票の「給与所得控除後の金額」引く「所得控除の額の合計額」
    :returns: 住民税年額
    """
    # 所得割
    city = val // 1000 * 1000 * 0.08
    pref = val // 1000 * 1000 * 0.02025 // 1

    # 調整控除の計算
    # 単身を想定
    # https://www.city.yokohama.lg.jp/kurashi/koseki-zei-hoken/zeikin/kojin-shiminzei-kenminzei/kojin-shiminzei-shosai/zeigakukoujo.html
    if val > 2000000:
        diff = max((50000 - val - 2000000), 50000)
    else:
        diff = min(50000, val)
    city_diff = diff * 0.04
    pref_diff = diff * 0.01
    city = (city - city_diff) // 100 * 100
    pref = (pref - pref_diff) // 100 * 100

    # 均等割
    city_fix = 4400
    pref_fix = 1800

    return city + pref + city_fix + pref_fix

# 社会保険料
# 4-6月の標準月額報酬から決まる
# https://www.kyoukaikenpo.or.jp/g7/cat330/sb3150/r02/r2ryougakuhyou9gatukara
def social_insurance(val):
    """
    TODO 微妙にあわない理由は何?
    :val: 4-6月の「標準月額報酬」
    :returns: 翌年の社会保険料合計額
    """
    if 165000 <= val and val < 175000:
        return 8440.500000 + 15555.000000
    if 175000 <= val and val < 185000:
        return 8937.000000 + 16470.000000
    if 185000 <= val and val < 195000:
        return 9433.500000 + 17385.000000
    if 195000 <= val and val < 210000:
        return 9930.000000 + 18300.000000
    if 210000 <= val and val < 230000:
        return 10923.000000 + 20130.000000
    if 230000 <= val and val < 250000:
        return 11916.000000 + 21960.000000
    if 250000 <= val and val < 270000:
        return 12909.000000 + 23790.000000
    if 270000 <= val and val < 290000:
        return 13902.000000 + 25620.000000
    if 290000 <= val and val < 310000:
        return 14895.000000 + 27450.000000
    if 310000 <= val and val < 330000:
        return 15888.000000 + 29280.000000
    if 330000 <= val and val < 350000:
        return 16881.000000 + 31110.000000
    if 350000 <= val and val < 370000:
        return 17874.000000 + 32940.000000
    if 370000 <= val and val < 395000:
        return 18867.000000 + 34770.000000
    if 395000 <= val and val < 425000:
        return 20356.500000 + 37515.000000
    if 425000 <= val and val < 455000:
        return 21846.000000 + 40260.000000
    if 455000 <= val and val < 485000:
        return 23335.500000 + 43005.000000
    if 485000 <= val and val < 515000:
        return 24825.000000 + 45750.000000
    if 515000 <= val and val < 545000:
        return 26314.500000 + 48495.000000
    raise Exception(f"{val} is out of range for social insurance.")

# 給与所得控除
# https://www.nta.go.jp/taxes/shiraberu/taxanswer/shotoku/1410.htm
# 所得税法別表第五(年末調整等のための給与所得控除後の給与等の金額の表)
def emp_income_deduction(val):
    """
    :val: 源泉徴収票の「支払金額」
    :returns: 源泉徴収票の「給与所得控除後の金額」
    """
    if 5772000 <= val and val < 5776000:
        return 4177600.000000
    if 5972000 <= val and val < 5976000:
        return 4337600.000000
    if 6172000 <= val and val < 6176000:
        return 4497600.000000
    if 5776000 <= val and val < 5780000:
        return 4180800.000000
    if 5976000 <= val and val < 5980000:
        return 4340800.000000
    if 6176000 <= val and val < 6180000:
        return 4500800.000000
    if 5780000 <= val and val < 5784000:
        return 4184000.000000
    if 5980000 <= val and val < 5984000:
        return 4344000.000000
    if 6180000 <= val and val < 6184000:
        return 4504000.000000
    if 5784000 <= val and val < 5788000:
        return 4187200.000000
    if 5984000 <= val and val < 5988000:
        return 4347200.000000
    if 6184000 <= val and val < 6188000:
        return 4507200.000000
    if 5788000 <= val and val < 5792000:
        return 4190400.000000
    if 5988000 <= val and val < 5992000:
        return 4350400.000000
    if 6188000 <= val and val < 6192000:
        return 4510400.000000
    if 5792000 <= val and val < 5796000:
        return 4193600.000000
    if 5992000 <= val and val < 5996000:
        return 4353600.000000
    if 6192000 <= val and val < 6196000:
        return 4513600.000000
    if 5796000 <= val and val < 5800000:
        return 4196800.000000
    if 5996000 <= val and val < 6000000:
        return 4356800.000000
    if 6196000 <= val and val < 6200000:
        return 4516800.000000
    if 5800000 <= val and val < 5804000:
        return 4200000.000000
    if 6000000 <= val and val < 6004000:
        return 4360000.000000
    if 6200000 <= val and val < 6204000:
        return 4520000.000000
    if 5804000 <= val and val < 5808000:
        return 4203200.000000
    if 6004000 <= val and val < 6008000:
        return 4363200.000000
    if 6204000 <= val and val < 6208000:
        return 4523200.000000
    if 5808000 <= val and val < 5812000:
        return 4206400.000000
    if 6008000 <= val and val < 6012000:
        return 4366400.000000
    if 6208000 <= val and val < 6212000:
        return 4526400.000000
    if 5812000 <= val and val < 5816000:
        return 4209600.000000
    if 6012000 <= val and val < 6016000:
        return 4369600.000000
    if 6212000 <= val and val < 6216000:
        return 4529600.000000
    if 5816000 <= val and val < 5820000:
        return 4212800.000000
    if 6016000 <= val and val < 6020000:
        return 4372800.000000
    if 6216000 <= val and val < 6220000:
        return 4532800.000000
    if 5820000 <= val and val < 5824000:
        return 4216000.000000
    if 6020000 <= val and val < 6024000:
        return 4376000.000000
    if 6220000 <= val and val < 6224000:
        return 4536000.000000
    if 5824000 <= val and val < 5828000:
        return 4219200.000000
    if 6024000 <= val and val < 6028000:
        return 4379200.000000
    if 6224000 <= val and val < 6228000:
        return 4539200.000000
    if 5828000 <= val and val < 5832000:
        return 4222400.000000
    if 6028000 <= val and val < 6032000:
        return 4382400.000000
    if 6228000 <= val and val < 6232000:
        return 4542400.000000
    if 5832000 <= val and val < 5836000:
        return 4225600.000000
    if 6032000 <= val and val < 6036000:
        return 4385600.000000
    if 6232000 <= val and val < 6236000:
        return 4545600.000000
    if 5836000 <= val and val < 5840000:
        return 4228800.000000
    if 6036000 <= val and val < 6040000:
        return 4388800.000000
    if 6236000 <= val and val < 6240000:
        return 4548800.000000
    if 5840000 <= val and val < 5844000:
        return 4232000.000000
    if 6040000 <= val and val < 6044000:
        return 4392000.000000
    if 6240000 <= val and val < 6244000:
        return 4552000.000000
    if 5844000 <= val and val < 5848000:
        return 4235200.000000
    if 6044000 <= val and val < 6048000:
        return 4395200.000000
    if 6244000 <= val and val < 6248000:
        return 4555200.000000
    if 5848000 <= val and val < 5852000:
        return 4238400.000000
    if 6048000 <= val and val < 6052000:
        return 4398400.000000
    if 6248000 <= val and val < 6252000:
        return 4558400.000000
    if 5852000 <= val and val < 5856000:
        return 4241600.000000
    if 6052000 <= val and val < 6056000:
        return 4401600.000000
    if 6252000 <= val and val < 6256000:
        return 4561600.000000
    if 5856000 <= val and val < 5860000:
        return 4244800.000000
    if 6056000 <= val and val < 6060000:
        return 4404800.000000
    if 6256000 <= val and val < 6260000:
        return 4564800.000000
    if 5860000 <= val and val < 5864000:
        return 4248000.000000
    if 6060000 <= val and val < 6064000:
        return 4408000.000000
    if 6260000 <= val and val < 6264000:
        return 4568000.000000
    if 5864000 <= val and val < 5868000:
        return 4251200.000000
    if 6064000 <= val and val < 6068000:
        return 4411200.000000
    if 6264000 <= val and val < 6268000:
        return 4571200.000000
    if 5868000 <= val and val < 5872000:
        return 4254400.000000
    if 6068000 <= val and val < 6072000:
        return 4414400.000000
    if 6268000 <= val and val < 6272000:
        return 4574400.000000
    if 5872000 <= val and val < 5876000:
        return 4257600.000000
    if 6072000 <= val and val < 6076000:
        return 4417600.000000
    if 6272000 <= val and val < 6276000:
        return 4577600.000000
    if 5876000 <= val and val < 5880000:
        return 4260800.000000
    if 6076000 <= val and val < 6080000:
        return 4420800.000000
    if 6276000 <= val and val < 6280000:
        return 4580800.000000
    if 5880000 <= val and val < 5884000:
        return 4264000.000000
    if 6080000 <= val and val < 6084000:
        return 4424000.000000
    if 6280000 <= val and val < 6284000:
        return 4584000.000000
    if 5884000 <= val and val < 5888000:
        return 4267200.000000
    if 6084000 <= val and val < 6088000:
        return 4427200.000000
    if 6284000 <= val and val < 6288000:
        return 4587200.000000
    if 5888000 <= val and val < 5892000:
        return 4270400.000000
    if 6088000 <= val and val < 6092000:
        return 4430400.000000
    if 6288000 <= val and val < 6292000:
        return 4590400.000000
    if 5892000 <= val and val < 5896000:
        return 4273600.000000
    if 6092000 <= val and val < 6096000:
        return 4433600.000000
    if 6292000 <= val and val < 6296000:
        return 4593600.000000
    if 5896000 <= val and val < 5900000:
        return 4276800.000000
    if 6096000 <= val and val < 6100000:
        return 4436800.000000
    if 6296000 <= val and val < 6300000:
        return 4596800.000000
    if 5900000 <= val and val < 5904000:
        return 4280000.000000
    if 6100000 <= val and val < 6104000:
        return 4440000.000000
    if 6300000 <= val and val < 6304000:
        return 4600000.000000
    if 5904000 <= val and val < 5908000:
        return 4283200.000000
    if 6104000 <= val and val < 6108000:
        return 4443200.000000
    if 6304000 <= val and val < 6308000:
        return 4603200.000000
    if 5908000 <= val and val < 5912000:
        return 4286400.000000
    if 6108000 <= val and val < 6112000:
        return 4446400.000000
    if 6308000 <= val and val < 6312000:
        return 4606400.000000
    if 5912000 <= val and val < 5916000:
        return 4289600.000000
    if 6112000 <= val and val < 6116000:
        return 4449600.000000
    if 6312000 <= val and val < 6316000:
        return 4609600.000000
    if 5916000 <= val and val < 5920000:
        return 4292800.000000
    if 6116000 <= val and val < 6120000:
        return 4452800.000000
    if 6316000 <= val and val < 6320000:
        return 4612800.000000
    if 5920000 <= val and val < 5924000:
        return 4296000.000000
    if 6120000 <= val and val < 6124000:
        return 4456000.000000
    if 6320000 <= val and val < 6324000:
        return 4616000.000000
    if 5924000 <= val and val < 5928000:
        return 4299200.000000
    if 6124000 <= val and val < 6128000:
        return 4459200.000000
    if 6324000 <= val and val < 6328000:
        return 4619200.000000
    if 5928000 <= val and val < 5932000:
        return 4302400.000000
    if 6128000 <= val and val < 6132000:
        return 4462400.000000
    if 6328000 <= val and val < 6332000:
        return 4622400.000000
    if 5932000 <= val and val < 5936000:
        return 4305600.000000
    if 6132000 <= val and val < 6136000:
        return 4465600.000000
    if 6332000 <= val and val < 6336000:
        return 4625600.000000
    if 5936000 <= val and val < 5940000:
        return 4308800.000000
    if 6136000 <= val and val < 6140000:
        return 4468800.000000
    if 6336000 <= val and val < 6340000:
        return 4628800.000000
    if 5940000 <= val and val < 5944000:
        return 4312000.000000
    if 6140000 <= val and val < 6144000:
        return 4472000.000000
    if 6340000 <= val and val < 6344000:
        return 4632000.000000
    if 5944000 <= val and val < 5948000:
        return 4315200.000000
    if 6144000 <= val and val < 6148000:
        return 4475200.000000
    if 6344000 <= val and val < 6348000:
        return 4635200.000000
    if 5948000 <= val and val < 5952000:
        return 4318400.000000
    if 6148000 <= val and val < 6152000:
        return 4478400.000000
    if 6348000 <= val and val < 6352000:
        return 4638400.000000
    if 5952000 <= val and val < 5956000:
        return 4321600.000000
    if 6152000 <= val and val < 6156000:
        return 4481600.000000
    if 6352000 <= val and val < 6356000:
        return 4641600.000000
    if 5956000 <= val and val < 5960000:
        return 4324800.000000
    if 6156000 <= val and val < 6160000:
        return 4484800.000000
    if 6356000 <= val and val < 6360000:
        return 4644800.000000
    if 5960000 <= val and val < 5964000:
        return 4328000.000000
    if 6160000 <= val and val < 6164000:
        return 4488000.000000
    if 6360000 <= val and val < 6364000:
        return 4648000.000000
    if 5964000 <= val and val < 5968000:
        return 4331200.000000
    if 6164000 <= val and val < 6168000:
        return 4491200.000000
    if 6364000 <= val and val < 6368000:
        return 4651200.000000
    if 5968000 <= val and val < 5972000:
        return 4334400.000000
    if 6168000 <= val and val < 6172000:
        return 4494400.000000
    if 6368000 <= val and val < 6372000:
        return 4654400.000000
    raise Exception(f"{val} is out of range for emp_income_deduction.")

# 基礎控除を足して返すだけ
# https://www.nta.go.jp/taxes/shiraberu/taxanswer/shotoku/1199.htm
def sum_of_income_deduction(val):
    """
    :val: 源泉徴収票の「社会保険料等の金額」 # 生命保険とかはとりあえず無視
    :returns: 源泉徴収票の「所得控除の額の合計額」
    """
    return val + 480000

print("源泉徴収票の「支払金額」を入力してください")
#all = int(input())
all = 6159797
print("源泉徴収票の「社会保険料等の金額」を入力してください")
#social = int(input())
social = 825237

print("源泉徴収票の「給与所得控除後の金額」")
emp_inc_ded = emp_income_deduction(all)
print(emp_inc_ded)

print("源泉徴収票の「所得控除の額の合計額」")
sum_of_inc_ded = sum_of_income_deduction(social)
print(sum_of_inc_ded)

print("源泉徴収票の「源泉徴収税額」")
inc_tax = income_tax(emp_inc_ded - sum_of_inc_ded)
print(inc_tax)

print("来年の住民税 年額:月額(端数)")
res_tax = resident_tax(emp_inc_ded - sum_of_inc_ded + 50000)
print(f"{res_tax}:{res_tax/12//100*100}({res_tax/12%100*12})")

print("現在の「標準月額報酬」を入力してください")
#normal_income = int(input())
normal_income = 300000
soc_ins = social_insurance(normal_income)
print("9月以降の社会保険料")
print(soc_ins)

###
print("月収が1万増えたらどうなるか")
soc_ins2 = social_insurance(normal_income + 10000 )
print("9月以降の社会保険料の増分")
print(soc_ins2 - soc_ins)

print("源泉徴収票の「源泉徴収税額」")
added = emp_inc_ded - sum_of_inc_ded + 120000 - soc_ins2 - soc_ins
inc_tax2 = income_tax(added)
print((inc_tax2 -  inc_tax)/12)

print("来年の住民税 年額:月額(端数)")
res_tax2 = resident_tax(added + 50000)
res_tax = res_tax2 - res_tax
print(f"{res_tax}:{res_tax/12//100*100}({res_tax/12%100*12})")
