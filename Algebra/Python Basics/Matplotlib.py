
# data types: numerical (discreet/continuous), categoric (ordinal, categorical)
# seven basic relationships between data: ranking, deviation, nominal comparison, 
# correlation, partial/total relationship, time series, distribution

### Matplotlib library ###

# two paradigms: procedural and *object-oriented*
# components: primitives, containers, container components (Figure, Axes, Tick)

import matplotlib.pyplot as plt
import math

# different visualizations:
# plot(X, Y, [fmt], ...), scatter(X, Y, ...), bar[h](x, height, ...)
# pie(X, [explode], ...), boxplot(X, ...), hist(X, bins, ...)
# fill[_between][x](...), text(x, y, text, ...)

# figure component:
# axes - list of Axes instances (include Subplot instances)
# patch - background Rectangle object instance
# images - list of FigureImage class instances
# legends - list of Legend class instances (not Axes.legends)
# lines - list of Line2D class instances (rarely used, see Axes.lines)
# patches - list of instances of the Patch class (rarely used, see Axes.patches)
# texts - list of Text class instances

# Axes component:
# artists - List of instances of the Artist class
# patch - Instances of the Rectangle class for the background of the view plane
# collections - List of instances of the Collection class
# images - List of instances of the AxesImage class
# legends - List of instances of the Legend class
# lines - List of instances of the Line2D class
# patches - List of instances of the Patch class
# texts - List of instances of the Text class
# xaxis - An instance of the matplotlib.axis.XAxis class
# yaxis - An instance of the matplotlib.axis.YAxis class

# Axes component methods:
# For ax instance of Axes() class:
# annotate - Annotation (ax.texts)
# bar - Rectangle (ax.patches)
# errorbar -  Line2D and Rectangle (ax.lines and ax.patches)
# fill - Polygon (ax.patches)
# hist - Rectangle (ax.patches)
# imshow - AxesImage (ax.images)
# legend - Legend (ax.legends)
# plot - Line2D (ax.lines)
# scatter - PolyCollection (ax.collections)
# text - Text (ax.texts)

### FROM PYTHON NOTEBOOKS ###

X = [1,2,3,4]
Y1 = [2,3,1,4]
Y2 = [4,3,2,1]

# having multiple graphs (plots) in one figure
fig, ax_list = plt.subplots(2)
ax_list[0].plot(X,Y1)

# having a 2x2 grid of graphs
fig, ax_matrix = plt.subplots(2,2)
ax_matrix[0][1].plot(X,Y1)
plt.close()

# list comprehension: [function(varName) for varName in setName]
X = [x for x in range(0,10)]
Y = [x**0.5 for x in X]     # **0.5 = sqrt

plt.scatter(X, Y, c=Y, cmap=plt.cm.Blues) # or plt.bar(X,Y)
plt.close()

# custom line styles
plt.plot(X,Y, linestyle = "dotted")
plt.plot(X,Y, dashes=[5,1,10,1])

# accentuated dots (markers), color
plt.plot(X,Y, marker='o', color='purple')

plt.close()
# multiple graphs one on another
X = [1,2,3,4]
Y1 = [2,3,1,4]
Y2 = [4,3,2,1]

fig, axes = plt.subplots()
axes.plot(X,Y1, color='green')
axes.plot(X,Y2, color='black')

# plot labels
plt.title("New plot", fontsize=24)
plt.xlabel("X label")
plt.ylabel("Y label")

plt.tick_params(axis='both', labelsize=16) # can be 'x' or 'y'

plt.close()
# pdf export
# plt.savefig("Figure1.png")  # can be .jpg and .pdf

X = [i for i in range(-100, 100)]
Y = [5 * x**2 + 10 for x in X]

fig, ax_m = plt.subplots(2, 2, constrained_layout = True)

# logarithmic scaling on axes
ax_m[1][1].plot(X, Y)
ax_m[1][1].set_xscale("log")
ax_m[1][1].set_yscale("log")
ax_m[1][1].set_ylabel("ylabel")

plt.show()

# converting dates

# from datetime import datetime
# dates = ['2022-12-27','2022-12-28','2022-12-29','2022-12-30','2022-12-31']
# X = [datetime.strptime(d, "%Y-%m-%d") for d in dates]
# plt.gcf().autofmt_xdate()