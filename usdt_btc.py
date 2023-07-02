#data = [{"date":1546300800,"high":3711.42000003,"low":3674.11000001,"open":3696.20229991,"close":3692.00000003,"volume":65168.66722286,"quoteVolume":17.64179572,"weightedAverage":3693.99284841},{"date":1546315200,"high":3725.47863624,"low":3689.1391001,"open":3699.11649999,"close":3720.95255,"volume":38727.26976631,"quoteVolume":10.42985058,"weightedAverage":3713.11836821},{"date":1546329600,"high":3729.42959998,"low":3699,"open":3722.22999999,"close":3713.50132428,"volume":85876.77474012,"quoteVolume":23.14474823,"weightedAverage":3710.42164238},{"date":1546344000,"high":3742.04999998,"low":3667.99593217,"open":3713.31051148,"close":3685.68145793,"volume":351455.15174927,"quoteVolume":95.01431484,"weightedAverage":3698.97054292},{"date":1546358400,"high":3701.77263227,"low":3638.95819695,"open":3685.68145785,"close":3701.33065007,"volume":428785.29726824,"quoteVolume":116.86055024,"weightedAverage":3669.20484618},{"date":1546372800,"high":3812,"low":3695.0000003,"open":3697.00000076,"close":3795.55974532,"volume":959285.39207767,"quoteVolume":256.20356202,"weightedAverage":3744.23128435},{"date":1546387200,"high":3808.70875567,"low":3763.75791224,"open":3796.24838735,"close":3775.80691489,"volume":340936.36552645,"quoteVolume":90.17019847,"weightedAverage":3781.03155267},{"date":1546401600,"high":3778.43204999,"low":3751.41443611,"open":3775.80691489,"close":3769.37572204,"volume":509014.52999243,"quoteVolume":135.0204779,"weightedAverage":3769.90614986},{"date":1546416000,"high":3800.77811493,"low":3769.82801491,"open":3770.5,"close":3786.68535702,"volume":492337.93020656,"quoteVolume":130.13966727,"weightedAverage":3783.15036863},{"date":1546430400,"high":3844.31279,"low":3780.43846881,"open":3786.76418525,"close":3801,"volume":627474.24682166,"quoteVolume":164.52712839,"weightedAverage":3813.80416082},{"date":1546444800,"high":3860.45133478,"low":3799.55404081,"open":3801.69656997,"close":3825.57962,"volume":642405.74136717,"quoteVolume":168.14110677,"weightedAverage":3820.63466636},{"date":1546459200,"high":3885.54389999,"low":3816.47610998,"open":3827,"close":3858.89981478,"volume":745787.12674931,"quoteVolume":193.59630052,"weightedAverage":3852.27984597},{"date":1546473600,"high":3861.97671467,"low":3818.88564822,"open":3856.00000016,"close":3839.57501492,"volume":307379.94214045,"quoteVolume":80.11325152,"weightedAverage":3836.81770878},{"date":1546488000,"high":3849.99999433,"low":3802.01091992,"open":3839.57501492,"close":3827.08884033,"volume":451422.81604352,"quoteVolume":117.94191223,"weightedAverage":3827.50124623},{"date":1546502400,"high":3830.67069996,"low":3787.03957749,"open":3827.08884033,"close":3808.41472966,"volume":415226.69907695,"quoteVolume":109.0462513,"weightedAverage":3807.80351572},{"date":1546516800,"high":3826.30666972,"low":3786.10000001,"open":3802.81768322,"close":3803.99590185,"volume":341452.03846145,"quoteVolume":89.71408854,"weightedAverage":3806.00242412},{"date":1546531200,"high":3803.99590185,"low":3731.00000003,"open":3803.99590185,"close":3750.27578776,"volume":679510.97285787,"quoteVolume":180.70290603,"weightedAverage":3760.37656386},{"date":1546545600,"high":3779.7,"low":3750.97577997,"open":3750.97577997,"close":3761.85757117,"volume":72155.0707857,"quoteVolume":19.14755485,"weightedAverage":3768.3699747},{"date":1546560000,"high":3781.33695432,"low":3737.71591645,"open":3763.83092408,"close":3779.66020004,"volume":84574.44950067,"quoteVolume":22.53331521,"weightedAverage":3753.30699067},{"date":1546574400,"high":3798.07925,"low":3766.6758,"open":3781.85,"close":3780.98000019,"volume":237735.2866061,"quoteVolume":62.88164887,"weightedAverage":3780.67831995},{"date":1546588800,"high":3797.28541273,"low":3751.54765853,"open":3783.1593,"close":3751.64765017,"volume":196776.06115464,"quoteVolume":52.19835315,"weightedAverage":3769.77527603},{"date":1546603200,"high":3763.34669502,"low":3701.35925415,"open":3754.09850979,"close":3726.89999932,"volume":302696.15431484,"quoteVolume":80.94675392,"weightedAverage":3739.4477191},{"date":1546617600,"high":3749.2085,"low":3716.69620001,"open":3724.35154963,"close":3741.59856999,"volume":202495.67473469,"quoteVolume":54.17371439,"weightedAverage":3737.89534306},{"date":1546632000,"high":3819.99291489,"low":3735.21082,"open":3737.32615,"close":3794.90259,"volume":449622.15622962,"quoteVolume":118.90982207,"weightedAverage":3781.20283423},{"date":1546646400,"high":3839.55900037,"low":3789.12672848,"open":3790.68631634,"close":3810.88110148,"volume":352704.55425755,"quoteVolume":92.46218444,"weightedAverage":3814.58167351}]

#for e in data:
#    print(e["close"])
import plotly.graph_objects as go

import pandas as pd
from datetime import datetime
import numpy as np

df = pd.read_csv('https://raw.githubusercontent.com/plotly/datasets/master/finance-charts-apple.csv')

high_list = df['AAPL.High']
low_list = df['AAPL.Low']

#higher_value_from_high_list = sorted(high_list, reverse=True, key=float)[:5]
lower_value_from_low_list = np.amin(low_list)

#print(higher_value_from_high_list)
print(high_list)
print(lower_value_from_low_list)

fig = go.Figure(data=[go.Candlestick(x=df['Date'],
                open=df['AAPL.Open'],
                high=df['AAPL.High'],
                low=df['AAPL.Low'],
                close=df['AAPL.Close'])])

fig.show()
