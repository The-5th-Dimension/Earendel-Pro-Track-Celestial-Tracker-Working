package com.earendel.earendel

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import com.google.firebase.database.FirebaseDatabase


class StarActivity : AppCompatActivity() , AdapterView.OnItemClickListener {

    private val databaseReference = FirebaseDatabase.getInstance().reference
    private val celestial = arrayOf("Achernar", "Achird", "Adhil", "Adhara", "Ain", "Acrab", "Acrux", "Acubens",
    "Albali", "Albireo", "Alchiba", "Alcor", "Alcyone", "Aldebaran", "Aldhanab", "Aldulfin", "Alderamin", "Aldhanab",
    "Aldulfin", "Aldhanab", "Aldulfin", "Aldulfin", "Aldulfin", "Alfirk", "Algenib", "Algorab", "Alhena", "Alioth",
    "Aljanah", "Alkaid", "Alkaphrah", "Alkes", "Almach", "Alnitak", "Alnilam", "Alphard", "Alphecca", "Alpheratz",
    "Alrakis", "Alrami", "Alsciaukat", "Alsafi", "Alshain", "Alshat", "Aludra", "Alzirr", "Angetenar", "Ankaa",
    "Anser", "Antares", "Arcturus", "Ashlesha", "Ascella", "Asellus Australis", "Asellus Borealis", "Asterope",
    "Atebyne", "Atlas", "Atik", "Atria", "Azha", "Azhidi", "Baten Kaitos", "Beemim", "Beid", "Bellatrix", "Betelgeuse",
    "Beta Hyadum", "Bharani", "Biene", "Botein", "Brachium", "Bunda", "Canopus", "Capella", "Castor", "Castula",
    "Cebalrai", "Celaeno", "Centaurus", "Cervantes", "Cet", "Chalawan", "Chamukuy", "Chara", "Chertan", "Copernicus",
    "Cursa", "Cygnus X1", "Dabih", "Dalim", "Deneb", "Deneb Algedi", "Diphda", "Diadem", "Dubhe", "Dziban", "Elnath",
    "Elkurud", "Eltanin", "Enif", "Errai", "Fafnir", "Fang", "Fomalhaut", "Fu Yue", "Furud", "Fuyue", "Gacrux",
    "Giausar", "Gienah", "Gomeisa", "Graffias", "Groombridge 34", "Groombridge 1830", "Gudja", "Hadar", "Haedus",
    "Hassaleh", "Hatysa", "Helvetios", "Homam", "Huixian", "Hyadum I", "Hyadum II", "Iklil", "Imai", "Intercrus",
    "Jabbah", "Jishui", "Kaffaljidhma", "Kang", "Kaus Australis", "Kaus Borealis", "Kaus Media", "Kaus Prior",
    "Kaus Posterior", "Keid", "Khan", "Kham Sufi", "Kochab", "Kornephoros", "Kruger 60", "Ku Tun", "Kuei","Kurhah",
    "Kornephoros", "Kruger 60", "Ku Tun", "Kuei", "Kurhah", "Kuznetsk", "Lacaille 8760", "Lacaille 9352",
    "Lalande 21185", "Larawag", "Lesath", "Libertas", "Lilii Borea", "Maasym", "Mara", "Marfik", "Markab", "Matar",
    "Megrez", "Meissa", "Mekbuda", "Menchib", "Menkar", "Menkent", "Menkib", "Menzar", "Mesarthim", "Micor", "Milkor",
    "Mimosa", "Mintaka", "Mirach", "Mira", "Mirfak", "Mirzam", "Misam", "Mothallah", "Muscida", "Nahn", "Nashira",
    "Nekkar", "Nembus", "Nihal", "Nunki", "Nusakan", "Okab", "Ogma", "Paikauhale", "Phecda", "Phact", "Philolaus",
    "Pipirima", "Pleione", "Polis", "Pollux", "Polaris", "Porrima", "Procyon", "Propus", "Proxima Centauri", "Psc 82 G",
    "Ptolom", "Rana", "Ran", "Rasalas", "Rasalgethi", "Rasalhague", "Ras Elased Australis", "Rasalhague", "Red Rectangle",
    "Regulus", "Rhamphorhynchus", "Rigel", "Rigil Kentaurus", "Ross 614", "Ross 686", "Ross 128", "Ross 154", "Ross 248",
    "Sabik", "Saclateni", "Sadalbari", "Sadachbia", "Sadalmelek", "Sadalmelik", "Sadalsuud", "Sadr", "Salafamakah",
    "Salm", "Sarin", "Scheat", "Schedar", "Schutzhund", "Secunda Hyadum", "Segin", "Sgr Alpha", "Shaula", "Sham",
    "Scheat", "Sheliak", "Sirius", "Skat", "Sol", "Spirograph", "Spica", "Struve 2398 A", "Struve 2398 B", "Sualocin",
    "Suhail", "Sulafat", "Syrma", "Talitha", "Tarf", "Taygeta", "Tegmine", "Tejat", "Terebellum", "Thuban","Tiaki",
    "Tianguan", "Tianyi", "Toliman", "Tonatiuh", "Torcular", "Tureis", "Unukalhai", "Unurgunite", "Uranus", "Ukdah",
    "Vega", "Veil Nebula", "Veritate", "Vindemiatrix", "Wezen", "Wolf 1061", "Wolf 359", "Wurren", "Xamidimura",
    "Xuange", "Yed Posterior", "Yed Prior", "Yildun", "Zaniah", "Zaurak", "Zavijava", "Zeta Reticuli", "Zhang",
    "Zeta Herculis", "Zeta Tucanae", "Zeta Virginis", "Zeta Aquilae", "Zeta Aurigae", "Zeta Centauri", "Zeta Draconis",
    "Zeta Ophiuchi", "Zeta Piscium", "Zeta Ursae Majoris", "Zeta Tauri", "Zeta Serpentis", "Zeta Leporis", "Zeta Persei",
    "Zeta Geminorum", "Zeta Reticuli", "Zhang", "Zosma", "Zubenelgenubi", "Zubenelhakrabi", "Zubeneschamali", "Zubenalmelek",
    "Zubenelgenubi", "Zubenelhakrabi", "Zubeneschamali", "Zubenalmelek", "Zubenelgenubi", "Zubenelhakrabi", "Zubeneschamali",
    "Zubenalmelek", "Zubenelgenubi", "Zubenelhakrabi", "Zubeneschamali", "Zubenalmelek")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_star)

        val listView: ListView = findViewById(R.id.star_list)
        val arrayAdapter: ArrayAdapter<String> = ArrayAdapter(applicationContext,
        android.R.layout.simple_list_item_1,celestial )

        listView.adapter = arrayAdapter
        listView.onItemClickListener = this
    }

    override fun onItemClick(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
        val options: String = parent?.getItemAtPosition(position) as String
        Toast.makeText(applicationContext, "$options is Selected",
        Toast.LENGTH_LONG).show()
        writeToFirebase(options)
    }

    private fun writeToFirebase(options: String) {
        val optionsRef = databaseReference.child("Planet")
        optionsRef.setValue(options)
    }
}