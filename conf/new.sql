CREATE TABLE roles (
    id INTEGER NOT NULL,
    roleid VARCHAR,
    PRIMARY KEY (id),
    UNIQUE (roleid)
);
CREATE TABLE users (
    id INTEGER NOT NULL,
    userid VARCHAR,
    passwd VARCHAR,
    name VARCHAR,
    email VARCHAR,
    enabled BOOL,
    expire BOOL,
    newtok BOOL,
    shell VARCHAR,
    homedir VARCHAR,
    PRIMARY KEY (id),
    UNIQUE (userid)
);
CREATE TABLE user_role_map (
    id INTEGER NOT NULL,
    roleid VARCHAR,
    userid VARCHAR,
    PRIMARY KEY (id),
    UNIQUE (roleid, userid),
    FOREIGN KEY(roleid) REFERENCES roles (id),
    FOREIGN KEY(userid) REFERENCES users (id)
);


INSERT INTO roles(id, roleid) VALUES(1, "Administrator");
INSERT INTO roles(id, roleid) VALUES(2, "Operator");
INSERT INTO roles(id, roleid) VALUES(3, "Viewer");

-- username : password
-- --------   --------
-- sangeeth : sangeeth123
-- bhagavan : bhagavan123
-- raghav   : raghav123

INSERT INTO users (id, userid, passwd, name, email, enabled, expire, newtok, shell, homedir) VALUES(1, "sangeeth", "$6$We6q4pZAEcTQuvh.$pHlIWVKMtMMGTOBFbjo1vUJodcK2LUiYpo2c.ZxAyFOHG7/XiRzEPn3BRwpZ74pnc86vrz2vushbNf.UoFDeT.", "Sangeeth Saravanaraj", "sangeeth.s@gmail.com", 1, 0, 0, "/bin/bash", "/home/sangeeth");
INSERT INTO users (id, userid, passwd, name, email, enabled, expire, newtok, shell, homedir) VALUES(2, "bhagavan", "$6$sMWbXUjP10wgYAvH$yElFJVsXvJ5wYh80upapAEZKm2yHbVcg2szzZIz7kf16oYohAjAfdG8SVhNQPz.n/hnM8S7Nef6SuhRU9DJdm0", "Bhagavan nagaraju", "bugs_cena@gmail.com", 1, 0, 0, "/bin/bash", "/home/bhagn");
INSERT INTO users (id, userid, passwd, name, email, enabled, expire, newtok, shell, homedir) VALUES(3, "raghav", "$6$0PTySn2tZkION46V$dFZyd1yb0OPwbddDv3lCyd3i8B0wmXJbSpt7NwdVuzft1FBXhQRopbGcQ4MZ23fVGEcocInMnkx3fFT/kXCYG0", "Raghavendra Swami", "raghav@gmail.com", 1, 0, 0, "/bin/bash", "/home/raghav");


INSERT INTO user_role_map (id, roleid, userid) VALUES(1, 1, 1);
INSERT INTO user_role_map (id, roleid, userid) VALUES(2, 2, 2);
INSERT INTO user_role_map (id, roleid, userid) VALUES(3, 3, 3);
INSERT INTO user_role_map (id, roleid, userid) VALUES(4, 2, 1);
INSERT INTO user_role_map (id, roleid, userid) VALUES(5, 3, 1);


