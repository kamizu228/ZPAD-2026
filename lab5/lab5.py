import streamlit as st
import pandas as pd
import plotly.express as px

st.set_page_config(layout="wide")

st.title("Лабораторна робота №5")

df = pd.read_csv("vhi_data.csv")

default_series = "VHI"
default_region = df["province_name"].unique()[0]
default_week = (int(df["week"].min()), int(df["week"].max()))
default_year = (int(df["year"].min()), int(df["year"].max()))

def reset():
    st.session_state.series = default_series
    st.session_state.region = default_region
    st.session_state.week = default_week
    st.session_state.year = default_year
    st.session_state.sort_asc = False
    st.session_state.sort_desc = False

left, right = st.columns([1, 2])

with left:
    st.header("Фільтри")

    series = st.selectbox(
        "Оберіть показник",
        ["VCI", "TCI", "VHI"],
        key="series"
    )

    region = st.selectbox(
        "Оберіть область",
        sorted(df["province_name"].unique()),
        key="region"
    )

    week_range = st.slider(
        "Тижні",
        min_value=int(df["week"].min()),
        max_value=int(df["week"].max()),
        value=(int(df["week"].min()), int(df["week"].max())),
        key="week"
    )

    year_range = st.slider(
        "Роки",
        min_value=int(df["year"].min()),
        max_value=int(df["year"].max()),
        value=(int(df["year"].min()), int(df["year"].max())),
        key="year"
    )

    sort_asc = st.checkbox("Сортування ↑", key="sort_asc")
    sort_desc = st.checkbox("Сортування ↓", key="sort_desc")

    if sort_asc and sort_desc:
        st.warning("Обидва сортування активні → не застосовується")

    st.button("Reset", on_click=reset)

filtered = df[
    (df["province_name"] == region) &
    (df["week"].between(week_range[0], week_range[1])) &
    (df["year"].between(year_range[0], year_range[1]))
]

comparison = df[
    (df["week"].between(week_range[0], week_range[1])) &
    (df["year"].between(year_range[0], year_range[1]))
]

# сортування
if sort_asc and not sort_desc:
    filtered = filtered.sort_values(by=series, ascending=True)

if sort_desc and not sort_asc:
    filtered = filtered.sort_values(by=series, ascending=False)

with right:
    tab1, tab2, tab3 = st.tabs(["Таблиця", "Графік", "Порівняння"])

    with tab1:
        st.dataframe(
            filtered[["province_name", "year", "week", "VCI", "TCI", "VHI"]],
            use_container_width=True
        )

    with tab2:
        if not filtered.empty:
            filtered = filtered.copy()
            filtered["time"] = filtered["year"].astype(str) + "-W" + filtered["week"].astype(str).str.zfill(2)

            fig = px.line(
                filtered,
                x="time",
                y=series,
                title=f"{series} для {region}"
            )
            st.plotly_chart(fig, use_container_width=True)
        else:
            st.warning("Немає даних")

    with tab3:
        avg = comparison.groupby("province_name")[series].mean().reset_index()

        fig2 = px.bar(
            avg,
            x="province_name",
            y=series,
            title="Порівняння по областях"
        )

        st.plotly_chart(fig2, use_container_width=True)