-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Dec 26, 2023 at 09:06 AM
-- Server version: 10.3.32-MariaDB
-- PHP Version: 8.0.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dht_chularat`
--

-- --------------------------------------------------------

--
-- Table structure for table `dht_alert`
--

CREATE TABLE `dht_alert` (
  `id_alert` int(11) NOT NULL,
  `id_device` varchar(100) NOT NULL,
  `temperature_alert` varchar(100) NOT NULL,
  `humidity_alert` varchar(100) NOT NULL,
  `Text_alert` varchar(100) NOT NULL,
  `time_alert` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `dht_device`
--

CREATE TABLE `dht_device` (
  `id_device` int(11) NOT NULL,
  `ip_device` varchar(100) NOT NULL,
  `temperature_device` varchar(100) NOT NULL,
  `humidity_device` varchar(100) NOT NULL,
  `name_device` varchar(100) NOT NULL,
  `mac_device` varchar(100) NOT NULL,
  `fw_ver_device` varchar(100) NOT NULL,
  `setting_temperature_low` varchar(100) NOT NULL,
  `setting_temperature_high` varchar(100) NOT NULL,
  `setting_humidity_low` varchar(100) NOT NULL,
  `setting_humidity_high` varchar(100) NOT NULL,
  `time_device` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `dht_device`
--
ALTER TABLE `dht_device`
  ADD PRIMARY KEY (`id_device`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `dht_device`
--
ALTER TABLE `dht_device`
  MODIFY `id_device` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
