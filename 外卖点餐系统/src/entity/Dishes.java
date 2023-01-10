package entity;

import java.time.LocalDate;

public class Dishes {
    private String dID;
    private String dname;
    private String dtype;
    private LocalDate dtime;
    private double price;
    private int dsales;
    private int dstocks;

    public Dishes() {
        // TODO Auto-generated constructor stub
    }

    public Dishes(String dID, String dname, String dtype, LocalDate dtime, double price, int dsales, int dstocks) {
        super();
        this.dID = dID;
        this.dname = dname;
        this.dtype = dtype;
        this.dtime = dtime;
        this.price = price;
        this.dsales = dsales;
        this.dstocks = dstocks;
    }

    public String getdID() {
        return dID;
    }

    public void setdID(String dID) {
        this.dID = dID;
    }

    public String getDname() {
        return dname;
    }

    public void setDname(String dname) {
        this.dname = dname;
    }

    public String getDtype() {
        return dtype;
    }

    public void setDtype(String dtype) {
        this.dtype = dtype;
    }

    public LocalDate getDtime() {
        return dtime;
    }

    public void setDtime(LocalDate dtime) {
        this.dtime = dtime;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getDsales() {
        return dsales;
    }

    public void setDsales(int dsales) {
        this.dsales = dsales;
    }

    public int getDstocks() {
        return dstocks;
    }

    public void setDstocks(int dstocks) {
        this.dstocks = dstocks;
    }

    @Override
    public String toString() {
        return "Dishes [菜品id：" + dID + ", 菜品名：" + dname + ", 菜品类型：" + dtype + ", 上架时间：" + dtime + ", 单价：" + price
                + ", 月销量：" + dsales + ", 总数量：" + dstocks + "]";
    }

}
