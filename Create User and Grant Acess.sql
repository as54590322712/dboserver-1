CREATE USER 'dboserver' IDENTIFIED BY 'dboserver';
GRANT ALL ON dbo.* TO 'dboserver'@'%' IDENTIFIED BY 'dboserver';
GRANT ALL ON dbo.* TO 'dboserver'@'localhost' IDENTIFIED BY 'dboserver';
FLUSH PRIVILEGES;