package entity;



import java.time.LocalDateTime;

public class User extends Human {
    private String uname;
    private String usex;
    private String uadress;
    private String utel;
    private LocalDateTime utime;
    public User() {
        // TODO Auto-generated constructor stub
    }
    public User(String ID, String uname, String usex, String pwd, String uadress, String utel, LocalDateTime utime) {
        super(ID,pwd);
        this.uname = uname;
        this.usex = usex;
        this.uadress = uadress;
        this.utel = utel;
        this.utime = utime;
    }

    public String getUname() {
        return uname;
    }
    public void setUname(String uname) {
        this.uname = uname;
    }
    public String getUsex() {
        return usex;
    }
    public void setUsex(String usex) {
        this.usex = usex;
    }
    public String getUadress() {
        return uadress;
    }
    public void setUadress(String uadress) {
        this.uadress = uadress;
    }
    public String getUtel() {
        return utel;
    }
    public void setUtel(String utel) {
        this.utel = utel;
    }
    public LocalDateTime getUtime() {
        return utime;
    }
    public void setUtime(LocalDateTime utime) {
        this.utime = utime;
    }
    @Override
    public String toString() {
        return "User [uID=" + super.getID() + ", uname=" + uname + ", usex=" + usex + ", upwd=" + super.getpwd() + ", uadress=" + uadress
                + ", utel=" + utel + ", utime=" + utime + "]";
    }

}