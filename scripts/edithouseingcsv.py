import os 
import pandas as pd
import altair as alt
import numpy as np
import pydeck as pdk
from tabulate import tabulate


def main():
    #price,area,bedrooms,bathrooms,stories,mainroad,guestroom,basement,hotwaterheating,airconditioning,parking,prefarea,furnishingstatus
    csv_housing = pd.read_csv('./data/housing.csv')
    csv_housing.drop(columns=[
    "bedrooms","bathrooms","stories","mainroad",
    "guestroom","basement","hotwaterheating","airconditioning",
    "parking","prefarea","furnishingstatus"], inplace=True)

    prices = csv_housing.drop(columns=["area"])
    areas  = csv_housing.drop(columns=["price"])

    areas.to_csv('./data/areas.csv', index=False)
    prices.to_csv('./data/prices.csv', index=False)
    #print(tabulate(csv_housing, headers='keys', tablefmt='psql'))


    print("done...") 

if __name__ == "__main__":
    main()
